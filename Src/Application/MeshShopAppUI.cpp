#include "MeshShopAppUI.h"
#include "../Common/ResourceManager.h"
#include "../Common/ToolKit.h"
#include "../Common/RenderSystem.h"
#include "AppManager.h"
#include "MeshShopApp.h"

namespace MagicApp
{
    MeshShopAppUI::MeshShopAppUI() :
        mIsProgressbarVisible(false),
        mTextInfo(NULL)
    {
    }

    MeshShopAppUI::~MeshShopAppUI()
    {
    }

    void MeshShopAppUI::Setup()
    {
        MagicCore::ResourceManager::LoadResource("../../Media/MeshShopApp", "FileSystem", "MeshShopApp");
        mRoot = MyGUI::LayoutManager::getInstance().loadLayout("MeshShopApp.layout");
        mRoot.at(0)->findWidget("But_DisplayMode")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &MeshShopAppUI::SwitchDisplayMode);
        mRoot.at(0)->findWidget("But_ImportMesh")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &MeshShopAppUI::ImportMesh);
        mRoot.at(0)->findWidget("But_ExportMesh")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &MeshShopAppUI::ExportMesh);
        mRoot.at(0)->findWidget("But_ConsolidateMesh")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &MeshShopAppUI::ConsolidateMesh);
        mRoot.at(0)->findWidget("But_ConsolidateTopology")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &MeshShopAppUI::ConsolidateTopology);
        mRoot.at(0)->findWidget("But_ReverseDirection")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &MeshShopAppUI::ReverseDirection);
        mRoot.at(0)->findWidget("But_RemoveMeshIsolatePart")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &MeshShopAppUI::RemoveMeshIsolatePart);
        mRoot.at(0)->findWidget("But_ConsolidateGeometry")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &MeshShopAppUI::ConsolidateGeometry);
        mRoot.at(0)->findWidget("But_FilterMesh")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &MeshShopAppUI::FilterMesh);
        mRoot.at(0)->findWidget("But_RemoveMeshNoise")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &MeshShopAppUI::RemoveMeshNoise);
        mRoot.at(0)->findWidget("But_SmoothMesh")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &MeshShopAppUI::SmoothMesh);
        mRoot.at(0)->findWidget("But_EnhanceMeshDetail")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &MeshShopAppUI::EnhanceMeshDetail);
        mRoot.at(0)->findWidget("But_SubdivideMesh")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &MeshShopAppUI::SubdivideMesh);
        mRoot.at(0)->findWidget("But_RefineMesh")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &MeshShopAppUI::RefineMesh);
        mRoot.at(0)->findWidget("But_DoRefineMesh")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &MeshShopAppUI::DoRefineMesh);
        mRoot.at(0)->findWidget("But_SimplifyMesh")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &MeshShopAppUI::SimplifyMesh);
        mRoot.at(0)->findWidget("But_DoSimplifyMesh")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &MeshShopAppUI::DoSimplifyMesh);
        mRoot.at(0)->findWidget("But_FillHole")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &MeshShopAppUI::FillHole);
        mRoot.at(0)->findWidget("But_FillHoleFlat")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &MeshShopAppUI::DoFillHoleFlat);
        mRoot.at(0)->findWidget("But_FillHoleSmooth")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &MeshShopAppUI::DoFillHoleSmooth);
        mRoot.at(0)->findWidget("But_AppJump")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &MeshShopAppUI::AppJump);
        mRoot.at(0)->findWidget("But_SampleMesh")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &MeshShopAppUI::SampleMesh);
        mRoot.at(0)->findWidget("But_ReliefApp")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &MeshShopAppUI::EnterReliefApp);
        mRoot.at(0)->findWidget("But_TextureApp")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &MeshShopAppUI::EnterTextureApp);
        mRoot.at(0)->findWidget("But_MeasureApp")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &MeshShopAppUI::EnterMeasureApp);
        mRoot.at(0)->findWidget("But_BackToHomepage")->castType<MyGUI::Button>()->eventMouseButtonClick += MyGUI::newDelegate(this, &MeshShopAppUI::BackToHomepage);

        mTextInfo = mRoot.at(0)->findWidget("Text_Info")->castType<MyGUI::TextBox>();
        mTextInfo->setTextColour(MyGUI::Colour(75.0 / 255.0, 131.0 / 255.0, 128.0 / 255.0));
    }

    void MeshShopAppUI::StartProgressbar(int range)
    {
        mRoot.at(0)->findWidget("APIProgress")->castType<MyGUI::ProgressBar>()->setVisible(true);
        mRoot.at(0)->findWidget("APIProgress")->castType<MyGUI::ProgressBar>()->setProgressRange(range);
        mRoot.at(0)->findWidget("APIProgress")->castType<MyGUI::ProgressBar>()->setProgressPosition(0);
        mIsProgressbarVisible = true;
    }

    void MeshShopAppUI::SetProgressbar(int value)
    {
        mRoot.at(0)->findWidget("APIProgress")->castType<MyGUI::ProgressBar>()->setProgressPosition(value);
    }

    void MeshShopAppUI::StopProgressbar()
    {
        mRoot.at(0)->findWidget("APIProgress")->castType<MyGUI::ProgressBar>()->setVisible(false);
        mIsProgressbarVisible = false;
    }

    bool MeshShopAppUI::IsProgressbarVisible()
    {
        return mIsProgressbarVisible;
    }

    void MeshShopAppUI::SetMeshInfo(int vertexCount, int triangleCount)
    {
        std::string textString = "";
        if (vertexCount > 0)
        {
            textString += "Vertex count = ";
            std::stringstream ss;
            ss << vertexCount;
            std::string numberString;
            ss >> numberString;
            textString += numberString;
            textString += "  Triangle count = ";
            ss.clear();
            ss << triangleCount;
            numberString.clear();
            ss >> numberString;
            textString += numberString;
            textString += "\n";
        }
        mTextInfo->setCaption(textString);
    }

    void MeshShopAppUI::Shutdown()
    {
        MyGUI::LayoutManager::getInstance().unloadLayout(mRoot);
        mRoot.clear();
        MagicCore::ResourceManager::UnloadResource("MeshShopApp");
    }

    void MeshShopAppUI::SwitchDisplayMode(MyGUI::Widget* pSender)
    {
        MeshShopApp* meshShop = dynamic_cast<MeshShopApp* >(AppManager::Get()->GetApp("MeshShopApp"));
        if (meshShop != NULL)
        {
            meshShop->SwitchDisplayMode();
        }
    }

    void MeshShopAppUI::ImportMesh(MyGUI::Widget* pSender)
    {
        MeshShopApp* meshShop = dynamic_cast<MeshShopApp* >(AppManager::Get()->GetApp("MeshShopApp"));
        if (meshShop != NULL)
        {
            meshShop->ImportMesh();
        }
    }

    void MeshShopAppUI::ExportMesh(MyGUI::Widget* pSender)
    {
        MeshShopApp* meshShop = dynamic_cast<MeshShopApp* >(AppManager::Get()->GetApp("MeshShopApp"));
        if (meshShop != NULL)
        {
            meshShop->ExportMesh();
        }
    }

    void MeshShopAppUI::ConsolidateMesh(MyGUI::Widget* pSender)
    {
        bool isVisible = mRoot.at(0)->findWidget("But_ConsolidateTopology")->castType<MyGUI::Button>()->isVisible();
        mRoot.at(0)->findWidget("But_ConsolidateTopology")->castType<MyGUI::Button>()->setVisible(!isVisible);
        mRoot.at(0)->findWidget("But_ReverseDirection")->castType<MyGUI::Button>()->setVisible(!isVisible);
        mRoot.at(0)->findWidget("But_ConsolidateGeometry")->castType<MyGUI::Button>()->setVisible(!isVisible);
        mRoot.at(0)->findWidget("But_RemoveMeshIsolatePart")->castType<MyGUI::Button>()->setVisible(!isVisible);
    }

    void MeshShopAppUI::ConsolidateTopology(MyGUI::Widget* pSender)
    {
        MeshShopApp* meshShop = dynamic_cast<MeshShopApp* >(AppManager::Get()->GetApp("MeshShopApp"));
        if (meshShop != NULL)
        {
            meshShop->ConsolidateTopology();
        }
    }

    void MeshShopAppUI::ReverseDirection(MyGUI::Widget* pSender)
    {
        MeshShopApp* meshShop = dynamic_cast<MeshShopApp* >(AppManager::Get()->GetApp("MeshShopApp"));
        if (meshShop != NULL)
        {
            meshShop->ReverseDirection();
        }
    }

    void MeshShopAppUI::RemoveMeshIsolatePart(MyGUI::Widget* pSender)
    {
        MeshShopApp* meshShop = dynamic_cast<MeshShopApp* >(AppManager::Get()->GetApp("MeshShopApp"));
        if (meshShop != NULL)
        {
            meshShop->RemoveMeshIsolatePart();
        }
    }

    void MeshShopAppUI::ConsolidateGeometry(MyGUI::Widget* pSender)
    {
        MeshShopApp* meshShop = dynamic_cast<MeshShopApp* >(AppManager::Get()->GetApp("MeshShopApp"));
        if (meshShop != NULL)
        {
            meshShop->ConsolidateGeometry();
        }
    }

    void MeshShopAppUI::FilterMesh(MyGUI::Widget* pSender)
    {
        bool isVisible = mRoot.at(0)->findWidget("But_SmoothMesh")->castType<MyGUI::Button>()->isVisible();
        mRoot.at(0)->findWidget("But_SmoothMesh")->castType<MyGUI::Button>()->setVisible(!isVisible);
        mRoot.at(0)->findWidget("But_RemoveMeshNoise")->castType<MyGUI::Button>()->setVisible(!isVisible);
        mRoot.at(0)->findWidget("But_EnhanceMeshDetail")->castType<MyGUI::Button>()->setVisible(!isVisible);
    }

    void MeshShopAppUI::RemoveMeshNoise(MyGUI::Widget* pSender)
    {
        MeshShopApp* meshShop = dynamic_cast<MeshShopApp* >(AppManager::Get()->GetApp("MeshShopApp"));
        if (meshShop != NULL)
        {
            meshShop->RemoveMeshNoise();
        }
    }

    void MeshShopAppUI::SmoothMesh(MyGUI::Widget* pSender)
    {
        MeshShopApp* meshShop = dynamic_cast<MeshShopApp* >(AppManager::Get()->GetApp("MeshShopApp"));
        if (meshShop != NULL)
        {
            meshShop->SmoothMesh();
        }
    }

    void MeshShopAppUI::EnhanceMeshDetail(MyGUI::Widget* pSender)
    {
        MeshShopApp* meshShop = dynamic_cast<MeshShopApp* >(AppManager::Get()->GetApp("MeshShopApp"));
        if (meshShop != NULL)
        {
            meshShop->EnhanceMeshDetail();
        }
    }

    void MeshShopAppUI::SubdivideMesh(MyGUI::Widget* pSender)
    {
        MeshShopApp* meshShop = dynamic_cast<MeshShopApp* >(AppManager::Get()->GetApp("MeshShopApp"));
        if (meshShop != NULL)
        {
            meshShop->LoopSubdivide();
        }        
    }

    void MeshShopAppUI::RefineMesh(MyGUI::Widget* pSender)
    {
        bool isVisible = mRoot.at(0)->findWidget("But_DoRefineMesh")->castType<MyGUI::Button>()->isVisible();
        isVisible = !isVisible;
        mRoot.at(0)->findWidget("But_DoRefineMesh")->castType<MyGUI::Button>()->setVisible(isVisible);
        mRoot.at(0)->findWidget("Edit_RefineTargetVertexCount")->castType<MyGUI::EditBox>()->setVisible(isVisible);
        if (isVisible)
        {
            int meshVertexCount = 0;
            MeshShopApp* meshShop = dynamic_cast<MeshShopApp* >(AppManager::Get()->GetApp("MeshShopApp"));
            if (meshShop != NULL)
            {
                meshVertexCount = meshShop->GetMeshVertexCount();
            }
            std::stringstream ss;
            std::string textString;
            ss << meshVertexCount;
            ss >> textString;
            mRoot.at(0)->findWidget("Edit_RefineTargetVertexCount")->castType<MyGUI::EditBox>()->setOnlyText(textString);
        }
    }

    void MeshShopAppUI::DoRefineMesh(MyGUI::Widget* pSender)
    {
        MeshShopApp* meshShop = dynamic_cast<MeshShopApp* >(AppManager::Get()->GetApp("MeshShopApp"));
        if (meshShop != NULL)
        {
            int meshVertexCount = meshShop->GetMeshVertexCount();
            std::string textString = mRoot.at(0)->findWidget("Edit_RefineTargetVertexCount")->castType<MyGUI::EditBox>()->getOnlyText();
            int targetVertexCount = std::atoi(textString.c_str());
            if (targetVertexCount < meshVertexCount)
            {
                std::stringstream ss;
                std::string textString;
                ss << meshVertexCount;
                ss >> textString;
                mRoot.at(0)->findWidget("Edit_RefineTargetVertexCount")->castType<MyGUI::EditBox>()->setOnlyText(textString);
            }
            else
            {
                meshShop->RefineMesh(targetVertexCount);
            }            
        }
    }

    void MeshShopAppUI::SimplifyMesh(MyGUI::Widget* pSender)
    {
        bool isVisible = mRoot.at(0)->findWidget("But_DoSimplifyMesh")->castType<MyGUI::Button>()->isVisible();
        isVisible = !isVisible;
        mRoot.at(0)->findWidget("But_DoSimplifyMesh")->castType<MyGUI::Button>()->setVisible(isVisible);
        mRoot.at(0)->findWidget("Edit_SimplifyTargetVertexCount")->castType<MyGUI::EditBox>()->setVisible(isVisible);
        if (isVisible)
        {
            int meshVertexCount = 0;
            MeshShopApp* meshShop = dynamic_cast<MeshShopApp* >(AppManager::Get()->GetApp("MeshShopApp"));
            if (meshShop != NULL)
            {
                meshVertexCount = meshShop->GetMeshVertexCount();
            }
            std::stringstream ss;
            std::string textString;
            ss << meshVertexCount;
            ss >> textString;
            mRoot.at(0)->findWidget("Edit_SimplifyTargetVertexCount")->castType<MyGUI::EditBox>()->setOnlyText(textString);
        }
    }

    void MeshShopAppUI::DoSimplifyMesh(MyGUI::Widget* pSender)
    {
        MeshShopApp* meshShop = dynamic_cast<MeshShopApp* >(AppManager::Get()->GetApp("MeshShopApp"));
        if (meshShop != NULL)
        {
            int meshVertexCount = meshShop->GetMeshVertexCount();
            std::string textString = mRoot.at(0)->findWidget("Edit_SimplifyTargetVertexCount")->castType<MyGUI::EditBox>()->getOnlyText();
            int targetVertexCount = std::atoi(textString.c_str());
            if (targetVertexCount > meshVertexCount || targetVertexCount < 3)
            {
                std::stringstream ss;
                std::string textString;
                ss << meshVertexCount;
                ss >> textString;
                mRoot.at(0)->findWidget("Edit_SimplifyTargetVertexCount")->castType<MyGUI::EditBox>()->setOnlyText(textString);
            }
            else
            {
                meshShop->SimplifyMesh(targetVertexCount);
            }            
        }
    }

    void MeshShopAppUI::AppJump(MyGUI::Widget* pSender)
    {
        bool isVisible = mRoot.at(0)->findWidget("But_SampleMesh")->castType<MyGUI::Button>()->isVisible();
        isVisible = !isVisible;
        mRoot.at(0)->findWidget("But_SampleMesh")->castType<MyGUI::Button>()->setVisible(isVisible);
        mRoot.at(0)->findWidget("But_ReliefApp")->castType<MyGUI::Button>()->setVisible(isVisible);
        mRoot.at(0)->findWidget("But_TextureApp")->castType<MyGUI::Button>()->setVisible(isVisible);
        mRoot.at(0)->findWidget("But_MeasureApp")->castType<MyGUI::Button>()->setVisible(isVisible);
    }

    void MeshShopAppUI::SampleMesh(MyGUI::Widget* pSender)
    {
        MeshShopApp* meshShop = dynamic_cast<MeshShopApp* >(AppManager::Get()->GetApp("MeshShopApp"));
        if (meshShop != NULL)
        {
            meshShop->SampleMesh();
        }
    }

    void MeshShopAppUI::EnterReliefApp(MyGUI::Widget* pSender)
    {
        MeshShopApp* meshShop = dynamic_cast<MeshShopApp* >(AppManager::Get()->GetApp("MeshShopApp"));
        if (meshShop != NULL)
        {
            meshShop->EnterReliefApp();
        }
    }
        
    void MeshShopAppUI::EnterTextureApp(MyGUI::Widget* pSender)
    {
        MeshShopApp* meshShop = dynamic_cast<MeshShopApp* >(AppManager::Get()->GetApp("MeshShopApp"));
        if (meshShop != NULL)
        {
            meshShop->EnterTextureApp();
        }
    }
    
    void MeshShopAppUI::EnterMeasureApp(MyGUI::Widget* pSender)
    {
        MeshShopApp* meshShop = dynamic_cast<MeshShopApp* >(AppManager::Get()->GetApp("MeshShopApp"));
        if (meshShop != NULL)
        {
            meshShop->EnterMeasureApp();
        }
    }

    void MeshShopAppUI::FillHole(MyGUI::Widget* pSender)
    {
        bool isVisible = mRoot.at(0)->findWidget("But_FillHoleFlat")->castType<MyGUI::Button>()->getVisible();
        isVisible = !isVisible;
        mRoot.at(0)->findWidget("But_FillHoleFlat")->castType<MyGUI::Button>()->setVisible(isVisible);
        mRoot.at(0)->findWidget("But_FillHoleSmooth")->castType<MyGUI::Button>()->setVisible(isVisible);
        MeshShopApp* meshShop = dynamic_cast<MeshShopApp* >(AppManager::Get()->GetApp("MeshShopApp"));
        if (meshShop != NULL)
        {
            meshShop->FindHole(isVisible);
        }
    }

    void MeshShopAppUI::DoFillHoleFlat(MyGUI::Widget* pSender)
    {
        MeshShopApp* meshShop = dynamic_cast<MeshShopApp* >(AppManager::Get()->GetApp("MeshShopApp"));
        if (meshShop != NULL)
        {
            meshShop->FillHole(true);
        }
    }

    void MeshShopAppUI::DoFillHoleSmooth(MyGUI::Widget* pSender)
    {
        MeshShopApp* meshShop = dynamic_cast<MeshShopApp* >(AppManager::Get()->GetApp("MeshShopApp"));
        if (meshShop != NULL)
        {
            meshShop->FillHole(false);
        }
    }

    void MeshShopAppUI::BackToHomepage(MyGUI::Widget* pSender)
    {
        MeshShopApp* meshShop = dynamic_cast<MeshShopApp* >(AppManager::Get()->GetApp("MeshShopApp"));
        if (meshShop != NULL)
        {
            if (meshShop->IsCommandInProgress())
            {
                return;
            }
            AppManager::Get()->SwitchCurrentApp("Homepage");
        }
    }
}

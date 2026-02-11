BatchJob()
{
    if (!m_Batch)
        return -1;


    PluginsArray arr = Manager::Get()->GetPluginManager()->GetCompilerOffers();
    if (arr.GetCount() == 0)
        return -2;

    cbCompilerPlugin* compiler = static_cast<cbCompilerPlugin*>(arr[0]);
    if (!compiler)
        return -3;

    if (!m_Clean && m_BatchTarget.Lower() == _T("ask"))
    {
        m_BatchTarget.Clear();
        cbProject* prj = Manager::Get()->GetProjectManager()->GetActiveProject();
        if (prj)
        {
            int idx = -1;
            wxString defTarget = prj->GetActiveBuildTarget();


            for (int i = 0; i < prj->GetBuildTargetsCount(); ++i)
            {
                ProjectBuildTarget* target = prj->GetBuildTarget(i);
                if (target->GetTitle().Matches(defTarget))
                {
                    idx = i;
                    break;
                }
            }
            idx = prj->SelectTarget(idx, false);
            if (idx == -1)
                return 0;
            m_BatchTarget = prj->GetBuildTarget(idx)->GetTitle();
        }
    }

    m_pBatchBuildDialog = m_Frame->GetBatchBuildDialog();
    PlaceWindow(m_pBatchBuildDialog);
    wxTaskBarIcon* tbIcon = new wxTaskBarIcon();
    tbIcon->SetIcon(
            #ifdef __WXMSW__
                wxICON(A_MAIN_ICON),
            #else
                wxIcon(app),
            #endif
                _("Building ") + wxFileNameFromPath(wxString(argv[argc-1])));

    m_pBatchBuildDialog->Show();

    if (m_ReBuild)
    {
        if (m_HasProject)
            compiler->Rebuild(m_BatchTarget);
        else if (m_HasWorkSpace)
            compiler->RebuildWorkspace(m_BatchTarget);
    }
    else if (m_Build)
    {
        if (m_HasProject)
            compiler->Build(m_BatchTarget);
        else if (m_HasWorkSpace)
            compiler->BuildWorkspace(m_BatchTarget);
    }
    else if (m_Clean)
    {
        if (m_HasProject)
            compiler->Clean(m_BatchTarget);
        else if (m_HasWorkSpace)
            compiler->CleanWorkspace(m_BatchTarget);
    }


    if (!m_Clean && m_pBatchBuildDialog)
        m_pBatchBuildDialog->ShowModal();

    if (tbIcon)
    {
        tbIcon->RemoveIcon();
        delete tbIcon;
    }

    if (m_pBatchBuildDialog->IsModal())
        m_pBatchBuildDialog->EndModal(wxID_OK);
    else
    {
        m_pBatchBuildDialog->Destroy();
        m_pBatchBuildDialog = nullptr;
    }

    return 0;
}

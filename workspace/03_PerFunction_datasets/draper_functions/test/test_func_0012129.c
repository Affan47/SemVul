CheckForExternallyModifiedProjects()
{
    if (Manager::IsBatchBuild())
        return;
    if (m_isCheckingForExternallyModifiedProjects)
        return;
    m_isCheckingForExternallyModifiedProjects = true;


    ProjectManager* ProjectMgr = Manager::Get()->GetProjectManager();
    if ( ProjectsArray* Projects = ProjectMgr->GetProjects())
    {
        bool reloadAll = false;


        std::vector<cbProject*> ProjectPointers;
        for (unsigned int idxProject = 0; idxProject < Projects->Count(); ++idxProject)
            ProjectPointers.push_back(Projects->Item(idxProject));

        for (unsigned int idxProject = 0; idxProject < ProjectPointers.size(); ++idxProject)
        {
            cbProject* pProject = ProjectPointers[idxProject];
            wxFileName fname(pProject->GetFilename());
            wxDateTime last = fname.GetModificationTime();
            if (last.IsLaterThan(pProject->GetLastModificationTime()))
            {
                int ret = -1;
                if (!reloadAll)
                {
                    Manager::Get()->GetLogManager()->Log(pProject->GetFilename());
                    wxString msg;
                    msg.Printf(_("Project %s is modified outside the IDE...\nDo you want to reload it (you will lose any unsaved work)?"),
                               pProject->GetFilename().c_str());
                    ConfirmReplaceDlg dlg(Manager::Get()->GetAppWindow(), false, msg);
                    dlg.SetTitle(_("Reload Project?"));
                    PlaceWindow(&dlg);
                    ret = dlg.ShowModal();
                    reloadAll = ret == crAll;
                }
                if (reloadAll || ret == crYes)
                    ProjectMgr->ReloadProject(pProject);
                else if (ret == crCancel)
                    break;
                else if (ret == crNo)
                    pProject->Touch();
            }
        }
    }
    m_isCheckingForExternallyModifiedProjects = false;
}

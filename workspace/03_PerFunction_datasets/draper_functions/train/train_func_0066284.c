OnCloseWorkspace(cb_unused wxCommandEvent& event)
{
    ProjectManager *prjManager = Manager::Get()->GetProjectManager();
    if (prjManager->GetWorkspace())
        prjManager->CloseWorkspace();
}

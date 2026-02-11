AddFileToProject(const wxString& filename, cbProject* project, wxArrayInt& targets)
{
    if (!project)
        project = GetActiveProject();

    int ret = DoAddFileToProject(filename, project, targets);
    if (ret > 0)
    {
        CodeBlocksEvent event(cbEVT_PROJECT_FILE_ADDED);
        event.SetProject(project);
        event.SetString(filename);
        Manager::Get()->GetPluginManager()->NotifyPlugins(event);
    }
    return ret;
}

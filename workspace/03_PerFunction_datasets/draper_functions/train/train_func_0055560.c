OnProjectActivated(CodeBlocksEvent& event)
{


    if (!ProjectManager::IsBusy() && IsAttached() && m_InitDone)
    {
        cbProject* project = event.GetProject();
        if (project && !m_NativeParser.GetParserByProject(project) && project->GetFilesCount() > 0)
            m_NativeParser.CreateParser(project);

        if (m_NativeParser.GetParser().ClassBrowserOptions().displayFilter == bdfProject)
            m_NativeParser.UpdateClassBrowser();
    }

    m_NeedsBatchColour = true;

    event.Skip();
}

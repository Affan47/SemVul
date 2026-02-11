DoParseProject(int index)
{
    if (m_cache[index].isParsed || index == 0)
        return;

    m_progress = new wxProgressDialog(_("Code Statistics plugin"),_("Parsing project files. Please wait..."));

    cbProject* project = Manager::Get()->GetProjectManager()->GetProjects()->Item(index - 1);
    m_currentFile = 0;
    m_numFiles = project->GetFilesCount();
    m_cache[index]=ParseProject(index, nullptr);

    m_progress->Update(100);
    delete m_progress;
    m_progress = nullptr;
    m_cache[index].isParsed = true;
}

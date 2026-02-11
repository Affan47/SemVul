addWorkspaceName(const char *name) {
    m_workspace_names.push_back(FbTk::FbStringUtil::LocaleStrToFb(name));
    Workspace *wkspc = getWorkspace(m_workspace_names.size()-1);
    if (wkspc)
        wkspc->setName(m_workspace_names.back());
}

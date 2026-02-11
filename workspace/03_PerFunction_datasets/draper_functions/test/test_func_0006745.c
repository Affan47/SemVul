updateWorkspaceName(unsigned int w) {
    Workspace *space = getWorkspace(w);
    if (space) {
        m_workspace_names[w] = space->name();
        m_workspacenames_sig.emit(*this);
        Fluxbox::instance()->save_rc();
    }
}

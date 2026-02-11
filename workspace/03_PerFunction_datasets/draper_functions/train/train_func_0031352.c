setWorkspace(long workspace) {
    if (workspace >= workspaceCount || workspace < 0)
        return ;
    if (workspace != fWinWorkspace) {
        fWinWorkspace = workspace;
        client()->setWinWorkspaceHint(fWinWorkspace);
        updateState();
        manager->focusLastWindow();
#ifdef CONFIG_TASKBAR
        updateTaskBar();
#endif
#ifdef CONFIG_WINLIST
        windowList->updateWindowListApp(fWinListItem);
#endif
        YFrameWindow *t = transient();

        while (t != 0) {
            t->setWorkspace(getWorkspace());
            t = t->nextTransient();
        }
    }
}

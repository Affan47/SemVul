addParent(EventHandler &ev, const FbWindow &win) {
    if (win.window() != 0)
        m_parent[win.window()] = &ev;
}

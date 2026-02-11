execute() {
    BScreen *screen = Fluxbox::instance()->mouseScreen();
    if (screen != 0)
        screen->leftWorkspace(m_param);
}

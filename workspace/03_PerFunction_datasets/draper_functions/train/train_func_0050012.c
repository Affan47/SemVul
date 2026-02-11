execute() {
    BScreen *screen = Fluxbox::instance()->mouseScreen();
    if (screen == 0)
        return;

    if (!m_menu.get() || screen->screenNumber() != m_menu->screenNumber()) {
        m_menu.reset(screen->createMenu(""));
        m_menu->setReloadHelper(new FbTk::AutoReloadHelper());
        m_menu->reloadHelper()->setReloadCmd(FbTk::RefCount<FbTk::Command<void> >(new FbTk::SimpleCommand<ShowCustomMenuCmd>(*this, &ShowCustomMenuCmd::reload)));
        m_menu->reloadHelper()->setMainFile(custom_menu_file);
    } else
        m_menu->reloadHelper()->checkReload();

    ::showMenu(*screen, *m_menu.get());
}

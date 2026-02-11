initMenus() {
    m_workspacemenu.reset(MenuCreator::createMenuType("workspacemenu", screenNumber()));
    m_rootmenu->reloadHelper()->setMainFile(Fluxbox::instance()->getMenuFilename());
    m_windowmenu->reloadHelper()->setMainFile(windowMenuFilename());
}

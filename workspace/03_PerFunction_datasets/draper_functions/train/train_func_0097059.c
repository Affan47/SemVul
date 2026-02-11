keyReleaseEvent(XKeyEvent &ke) {
    if (m_cycling) {
        unsigned int state = FbTk::KeyUtil::instance().cleanMods(ke.state);
        state &= ~FbTk::KeyUtil::instance().keycodeToModmask(ke.keycode);

        if (state)
            return;

        m_cycling = false;
        focusControl().stopCyclingFocus();
    }
    if (!Fluxbox::instance()->keys()->inKeychain())
        FbTk::EventManager::instance()->ungrabKeyboard();
}

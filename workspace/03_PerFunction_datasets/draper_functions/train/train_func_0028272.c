shutdown() {
    if (m_shutdown)
        return;

    m_shutdown = true;

    XSetInputFocus(FbTk::App::instance()->display(), PointerRoot, None, CurrentTime);

    STLUtil::forAll(m_screen_list, mem_fun(&BScreen::shutdown));

    sync(false);
}

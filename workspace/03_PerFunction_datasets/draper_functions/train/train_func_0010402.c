grabWindow(Window win) {
    if (!m_keylist)
        return;


    WindowMap::iterator win_it = m_window_map.find(win);
    if (win_it == m_window_map.end())
        return;

    m_handler_map[win]->grabButtons();
    t_key::keylist_t::iterator it = m_keylist->keylist.begin();
    t_key::keylist_t::iterator it_end = m_keylist->keylist.end();
    for (; it != it_end; ++it) {

        if ((win_it->second & Keys::GLOBAL) > 0 && (*it)->type == KeyPress)
            FbTk::KeyUtil::grabKey((*it)->key, (*it)->mod, win);

        else if ((win_it->second & (*it)->context & ~Keys::ON_DESKTOP) > 0) {

            if ((*it)->type == ButtonPress || (*it)->type == ButtonRelease || (*it)->type == MotionNotify) {
                FbTk::KeyUtil::grabButton((*it)->key, (*it)->mod, win, ButtonPressMask|ButtonReleaseMask|ButtonMotionMask);
            }
        }
    }
}

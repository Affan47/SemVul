enterNotifyEvent(XCrossingEvent &ce) {

    if (menu.frame != ce.window)
        return;

    menu.x_shift = x(), menu.y_shift = y();
    if (x() + width() > m_screen_x + m_screen_width) {
        menu.x_shift = m_screen_x + m_screen_width - width() - 2*theme().borderWidth();
        m_shifted = true;
    } else if (x() < 0) {
        menu.x_shift = 0;
        m_shifted = true;
    }

    if (y() + height() + 2*theme().borderWidth() > m_screen_height) {
        menu.y_shift = m_screen_height - height() - 2*theme().borderWidth();
        m_shifted = true;
    } else if (y() + (signed) theme().titleHeight() < 0) {
        menu.y_shift = 0;
        m_shifted = true;
    }


    if (m_shifted) {
        menu.window.move(menu.x_shift, menu.y_shift);
        menu.title.parentMoved();
        menu.frame.parentMoved();
        clearWindow();
    }

    if (validIndex(m_which_sub)) {
        MenuItem *tmp = menuitems[m_which_sub];
        if (tmp->submenu()->isVisible()) {
            int sbl = (ce.x / menu.item_w), i = (ce.y / theme().itemHeight()),
                w = (sbl * menu.persub) + i;

            if (w != m_which_sub && (! tmp->submenu()->isTorn())) {
                tmp->submenu()->internal_hide();

                clearItem(m_which_sub);
                m_which_sub = -1;
            }
        }
    }
}

buttonPressEvent(XButtonEvent &be) {
    if (be.window != frame.window.window())
        return;

    if (be.button == Button3) {
        if (! m_slitmenu.isVisible()) {
            screen().placementStrategy()
                .placeAndShowMenu(m_slitmenu, be.x_root, be.y_root, false);
        } else
            m_slitmenu.hide();
    }
}

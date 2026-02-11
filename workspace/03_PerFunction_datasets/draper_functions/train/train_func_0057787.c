moveResize(int new_x, int new_y,
                               unsigned int new_width, unsigned int new_height,
                               bool send_event) {

    m_placed = true;
    send_event = send_event || frame().x() != new_x || frame().y() != new_y;

    if ((new_width != frame().width() || new_height != frame().height()) &&
        isResizable() && !isShaded()) {

        if ((((signed) frame().width()) + new_x) < 0)
            new_x = 0;
        if ((((signed) frame().height()) + new_y) < 0)
            new_y = 0;

        frame().moveResize(new_x, new_y, new_width, new_height);
        setFocusFlag(m_focused);

        send_event = true;
    } else if (send_event)
        frame().move(new_x, new_y);

    if (send_event && ! moving) {
        sendConfigureNotify();
    }


    if (!moving) {
        m_last_resize_x = new_x;
        m_last_resize_y = new_y;


        screen().focusControl().ignoreAtPointer();
    }

}

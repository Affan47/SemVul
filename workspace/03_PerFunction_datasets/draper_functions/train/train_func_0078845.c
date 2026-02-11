dispatch(Window win, XEvent &ev, bool parent) {
    EventHandler *evhand = 0;
    if (parent) {
        EventHandlerMap::iterator it = m_parent.find(win);
        if (it == m_parent.end())
            return;
        else
            evhand = it->second;
    } else {
        win = getEventWindow(ev);
        EventHandlerMap::iterator it = m_eventhandlers.find(win);
        if (it == m_eventhandlers.end())
            return;
        else
            evhand = it->second;
    }

    if (evhand == 0)
        return;

    switch (ev.type) {
    case KeyPress:
        evhand->keyPressEvent(ev.xkey);
    break;
    case KeyRelease:
        evhand->keyReleaseEvent(ev.xkey);
    break;
    case ButtonPress:
        evhand->buttonPressEvent(ev.xbutton);
    break;
    case ButtonRelease:
        evhand->buttonReleaseEvent(ev.xbutton);
    break;
    case MotionNotify:
        evhand->motionNotifyEvent(ev.xmotion);
    break;
    case Expose:
        evhand->exposeEvent(ev.xexpose);
    break;
    case EnterNotify:
        if (ev.xcrossing.mode != NotifyGrab &&
            ev.xcrossing.mode != NotifyUngrab)
            evhand->enterNotifyEvent(ev.xcrossing);
    break;
    case LeaveNotify:
        if (ev.xcrossing.mode != NotifyGrab &&
            ev.xcrossing.mode != NotifyUngrab)
            evhand->leaveNotifyEvent(ev.xcrossing);
    break;
    default:
        evhand->handleEvent(ev);
    break;
    };


    Window root, parent_win, *children = 0;
    unsigned int num_children;
    if (XQueryTree(FbTk::App::instance()->display(), win,
                   &root, &parent_win, &children, &num_children) != 0) {
        if (children != 0)
            XFree(children);

        if (parent_win != 0 &&
            parent_win != root) {
            if (m_parent[parent_win] == 0)
                return;


            dispatch(parent_win, ev, true);
        }
    }

}

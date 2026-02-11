x11EventFilter(XEvent *ev) {
    if (isBadWindow()) {
        return false;
    }

    XAnyEvent *event = reinterpret_cast<XAnyEvent *> (ev);

    if (event->window == m_window) {
        if (event->type == DestroyNotify) {
            destroyEvent();
            return true;
        } else if (event->type == PropertyNotify) {
            return propertyChangeEvent(reinterpret_cast<XPropertyEvent *> (event)->atom);
        } else if (event->type == VisibilityNotify) {
            if (reinterpret_cast<XVisibilityEvent *> (event)->state == VisibilityFullyObscured) {
                obscureEvent();
                return true;
            }
        } else if (event->type == FocusOut) {
            focusLostEvent();
            return true;
        } else if (event->type == MapNotify) {
            m_iconified = false;
            updateToggleAction();
            return true;
        } else if (event->type == UnmapNotify) {
            m_iconified = true;
            updateToggleAction();
            return true;
        }
    }
    return false;
}

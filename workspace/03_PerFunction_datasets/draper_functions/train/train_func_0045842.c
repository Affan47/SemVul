x11Event(XEvent *event)
{
    if (m_xkbAvailable) {
        XkbEvent *kbevt;
        unsigned int stateMask = XkbModifierStateMask | XkbModifierBaseMask |
                                 XkbModifierLatchMask | XkbModifierLockMask;
        if (event->type == m_xkbEv + XkbEventCode &&
            (kbevt = (XkbEvent*)event) != 0)
        {
            if (kbevt->any.xkb_type == XkbMapNotify) {
                xkbUpdateModifierMapping();
            } else if (kbevt->any.xkb_type == XkbStateNotify) {
                XkbStateNotifyEvent *snevent = (XkbStateNotifyEvent*)event;
                if (snevent->changed & stateMask) {
                    xkbModifierStateChanged(snevent->mods, snevent->latched_mods,
                                            snevent->locked_mods);
                } else if (snevent->changed & XkbPointerButtonMask) {
                    xkbButtonStateChanged(snevent->ptr_buttons);
                }
            }
            return false;
        }
    }

    return false;
}

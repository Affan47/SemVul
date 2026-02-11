filterEvent(const XEvent &xev) {
    if (xev.type == PropertyNotify) {

#if 0
        if (xev.xproperty.window == desktop->handle() &&
            xev.xproperty.atom == _XA_NET_CURRENT_DESKTOP)
        {
            update();
        }
#endif
    } else if (xev.type == ClientMessage) {
        if (xev.xclient.window == desktop->handle() &&
            xev.xproperty.atom == _XA_ICEWMBG_QUIT)
        {
            exit(0);
        }
        if (xev.xclient.window == desktop->handle() &&
            xev.xproperty.atom == _XA_ICEWMBG_RESTART)
        {
            execlp(ICEWMBGEXE, ICEWMBGEXE, (void *)NULL);
        }
    }

    return YXApplication::filterEvent(xev);
}

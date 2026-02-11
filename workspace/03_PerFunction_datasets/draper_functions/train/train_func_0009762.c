setNumberOfDesktops(int numberOfDesktops)
{
#ifdef    NETWMDEBUG
    fprintf(stderr,
     "NETRootInfo::setNumberOfDesktops: setting desktop count to %d (%s)\n",
     numberOfDesktops, (role == WindowManager) ? "WM" : "Client");
#endif
    if (role == WindowManager) {
        p->number_of_desktops = numberOfDesktops;
        long d = numberOfDesktops;
        XChangeProperty(p->display, p->root, net_number_of_desktops, XA_CARDINAL, 32,
         PropModeReplace, (unsigned char *) &d, 1);
    } else {
        XEvent e;
        e.xclient.type = ClientMessage;
        e.xclient.message_type = net_number_of_desktops;
        e.xclient.display = p->display;
        e.xclient.window = p->root;
        e.xclient.format = 32;
        e.xclient.data.l[0] = numberOfDesktops;
        e.xclient.data.l[1] = 0l;
        e.xclient.data.l[2] = 0l;
        e.xclient.data.l[3] = 0l;
        e.xclient.data.l[4] = 0l;
        XSendEvent(p->display, p->root, False, netwm_sendevent_mask, &e);
    }
}

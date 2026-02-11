setDesktop(int desktop)
{
    if (p->mapping_state_dirty)
        updateWMState();
    if (role == Client && p->mapping_state != Withdrawn) {

        if (desktop == 0)
            return;
        XEvent e;
        e.xclient.type = ClientMessage;
        e.xclient.message_type = net_wm_desktop;
        e.xclient.display = p->display;
        e.xclient.window = p->window;
        e.xclient.format = 32;
        e.xclient.data.l[0] = desktop == OnAllDesktops ? OnAllDesktops : desktop - 1;
        e.xclient.data.l[1] = 0l;
        e.xclient.data.l[2] = 0l;
        e.xclient.data.l[3] = 0l;
        e.xclient.data.l[4] = 0l;
        XSendEvent(p->display, p->root, False, netwm_sendevent_mask, &e);
    } else {

        p->desktop = desktop;
        long d = desktop;
        if (d != OnAllDesktops) {
            if (d == 0) {
                XDeleteProperty(p->display, p->window, net_wm_desktop);
                return;
            }
            d -= 1;
        }
        XChangeProperty(p->display, p->window, net_wm_desktop, XA_CARDINAL, 32,
         PropModeReplace, (unsigned char *) &d, 1);
    }
}

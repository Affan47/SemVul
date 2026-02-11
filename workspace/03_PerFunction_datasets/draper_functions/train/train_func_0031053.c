move_window_to_desktop(guint desktop_num, GtkWidget * window) {

    if (desktop_num+1 > get_all_desktops()) return;

    display = GDK_DISPLAY();
    root_win = GDK_WINDOW_XWINDOW(gdk_get_default_root_window());
    displays = gdk_drawable_get_display (window->window);

    xevent.type              = ClientMessage;
    xevent.xclient.type      = ClientMessage;
    xevent.xclient.serial = 0;
    xevent.xclient.send_event = True;
    xevent.xclient.display   = display;
    xevent.xclient.window    = GDK_WINDOW_XWINDOW (window->window);
    xevent.xclient.message_type = gdk_x11_get_xatom_by_name_for_display (displays, "_NET_WM_DESKTOP");
    xevent.xclient.format    = 32;
    xevent.xclient.data.l[0] = desktop_num;
    xevent.xclient.data.l[1] = CurrentTime;
    xevent.xclient.data.l[2] = 0;
    xevent.xclient.data.l[3] = 0;
    xevent.xclient.data.l[4] = 0;

    XSendEvent(display, root_win, False, SubstructureNotifyMask | SubstructureRedirectMask, &xevent);

    XFlush(display);
}

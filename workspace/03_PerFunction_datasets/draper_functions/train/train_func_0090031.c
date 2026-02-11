tk_callback_scroll_event (GtkWidget *widget, GdkEventScroll *event, task *tk)
{
    ENTER;
    if (event->direction == GDK_SCROLL_UP) {
        GdkWindow *gdkwindow;

        gdkwindow = gdk_xid_table_lookup (tk->win);
        if (gdkwindow)
            gdk_window_show (gdkwindow);
        else
            XMapRaised (GDK_DISPLAY(), tk->win);
        XSetInputFocus (GDK_DISPLAY(), tk->win, RevertToNone, CurrentTime);
        DBG("XMapRaised  %x\n", tk->win);
    } else if (event->direction == GDK_SCROLL_DOWN) {
        DBG("tb->ptk = %x\n", (tk->tb->ptk) ? tk->tb->ptk->win : 0);
        XIconifyWindow (GDK_DISPLAY(), tk->win, DefaultScreen(GDK_DISPLAY()));
        DBG("XIconifyWindow %x\n", tk->win);
    }

    XSync (gdk_display, False);
    RET(TRUE);
}

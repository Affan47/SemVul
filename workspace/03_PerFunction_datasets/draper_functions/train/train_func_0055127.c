bs_icon_window_show_at(BSIconWindow *iw, gint desktop, gint x, gint y)
{
    trace("mapping window %ld to %d, %d", iw->window, x, y);
    XMoveWindow(GDK_DISPLAY(), iw->window, x, y);
    iw->has_position = TRUE;

    set_hints(iw->window, iw->sticky, desktop);
    XMapWindow(GDK_DISPLAY(), iw->window);
    send_desktop_message(iw, desktop);
}

destroy_windows(BSIconWindow *iw)
{
    if (iw->dst_gdkwindow) {
        g_object_unref(iw->dst_gdkwindow);
        iw->dst_gdkwindow = NULL;
        XDestroyWindow(GDK_DISPLAY(), iw->dst_window);
        iw->dst_window = None;
    }

    if (iw->gdkwindow) {
        g_object_unref(iw->gdkwindow);
        iw->gdkwindow = NULL;
        XDestroyWindow(GDK_DISPLAY(), iw->window);
        iw->window = None;
    }
}

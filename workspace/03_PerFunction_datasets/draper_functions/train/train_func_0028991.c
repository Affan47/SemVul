_setIcon (GtkWidget *window)
    {
        XAP_Frame *lff = XAP_App::getApp()->getLastFocussedFrame();
        XAP_UnixFrameImpl *pUnixFrameImpl = static_cast<XAP_UnixFrameImpl *>(lff->getFrameImpl());
        GtkWidget *top = gtk_widget_get_toplevel(pUnixFrameImpl->getTopLevelWindow());

        if (gtk_widget_is_toplevel(top))
        {
            GdkPixbuf *icon = gtk_window_get_icon(GTK_WINDOW(top));

            if (icon) gtk_window_set_icon(GTK_WINDOW(window), icon);
        }
    }

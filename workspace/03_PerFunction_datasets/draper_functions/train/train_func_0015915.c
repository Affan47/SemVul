window_open_link_cb (DhWindow *window,
                     const char *location,
                     DhOpenLinkFlags flags)
{
        DhWindowPriv *priv;
        priv = window->priv;

        if (flags & DH_OPEN_LINK_NEW_TAB) {
                window_open_new_tab (window, location, FALSE);
        }
        else if (flags & DH_OPEN_LINK_NEW_WINDOW) {
                GtkWidget *new_window;
                new_window = dh_base_new_window (priv->base);
                gtk_widget_show (new_window);
        }
}

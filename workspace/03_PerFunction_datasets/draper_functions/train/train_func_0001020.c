gdl_dock_floating_configure_event_cb (GtkWidget         *widget,
                                      GdkEventConfigure *event,
                                      gpointer           user_data)
{
    GdlDock *dock;

    g_return_val_if_fail (user_data != NULL && GDL_IS_DOCK (user_data), TRUE);

    dock = GDL_DOCK (user_data);
    dock->priv->float_x = event->x;
    dock->priv->float_y = event->y;
    dock->priv->width = event->width;
    dock->priv->height = event->height;

    return FALSE;
}

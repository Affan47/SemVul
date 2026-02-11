do_pointer_ungrab(VncDisplay *obj, gboolean quiet)
{
    VncDisplayPrivate *priv = obj->priv;


    if (!priv->grab_keyboard)
        do_keyboard_ungrab(obj, quiet);

    do_pointer_ungrab_all(gtk_widget_get_window(GTK_WIDGET(obj)));
    priv->in_pointer_grab = FALSE;

    if (priv->absolute)
        do_pointer_hide(obj);

    if (!quiet)
        g_signal_emit(obj, signals[VNC_POINTER_UNGRAB], 0);
}

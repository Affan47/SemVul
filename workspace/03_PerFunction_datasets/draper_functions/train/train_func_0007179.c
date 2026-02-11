start_timer (InputPadGtkButton *button)
{
    GtkSettings *settings;
    guint timeout;

    g_return_if_fail (button->priv != NULL);

    if (button->priv->timer != 0) {
        return;
    }
    settings = gtk_widget_get_settings (GTK_WIDGET (button));
    g_object_get (settings, "gtk-timeout-initial", &timeout, NULL);
    button->priv->timer = gdk_threads_add_timeout (timeout,
                                                   (GSourceFunc) button_timer_cb,
                                                   (gpointer) button);
}

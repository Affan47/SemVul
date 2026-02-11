gwy_widget_set_activate_on_unfocus(GtkWidget *widget,
                                   gboolean activate)
{
    gulong id;

    g_return_if_fail(GTK_IS_WIDGET(widget));
    g_return_if_fail(GTK_WIDGET_GET_CLASS(widget)->activate_signal);
    id = g_signal_handler_find(widget, G_SIGNAL_MATCH_FUNC,
                               0, 0, NULL, activate_on_unfocus, NULL);
    if (id && !activate)
        g_signal_handler_disconnect(widget, id);
    if (!id && activate)
        g_signal_connect(widget, "focus-out-event",
                         G_CALLBACK(activate_on_unfocus), NULL);
}

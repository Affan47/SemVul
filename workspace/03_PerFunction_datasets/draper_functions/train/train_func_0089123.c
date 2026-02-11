gwy_widget_get_activate_on_unfocus(GtkWidget *widget)
{
    g_return_val_if_fail(GTK_IS_WIDGET(widget), FALSE);
    return !!g_signal_handler_find(widget, G_SIGNAL_MATCH_FUNC,
                                   0, 0, NULL, activate_on_unfocus, NULL);
}

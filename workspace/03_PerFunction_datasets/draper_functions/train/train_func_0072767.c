handle_window_dialog_up (GSManager *manager,
                         GSWindow  *window)
{
        GSList *l;

        g_return_if_fail (manager != NULL);
        g_return_if_fail (GS_IS_MANAGER (manager));

        gs_debug ("Handling dialog up");

        g_signal_emit (manager, signals [AUTH_REQUEST_BEGIN], 0);

        manager->priv->dialog_up = TRUE;

        for (l = manager->priv->windows; l; l = l->next) {
                if (l->data != window) {
                        gtk_widget_set_sensitive (GTK_WIDGET (l->data), FALSE);
                }
        }


        gs_grab_move_to_window (manager->priv->grab,
                                gs_window_get_gdk_window (window),
                                gs_window_get_screen (window),
                                FALSE);


        gs_grab_release_mouse (manager->priv->grab);
}

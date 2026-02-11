nemo_status_bar_sync_button_states (NemoStatusBar *bar)
{
    const gchar *sidebar_id = nemo_window_get_sidebar_id (NEMO_WINDOW (bar->window));

    gboolean sidebar_visible = nemo_window_get_show_sidebar (NEMO_WINDOW (bar->window));

    if (sidebar_visible) {
        gtk_widget_show (bar->tree_button);
        gtk_widget_show (bar->places_button);
        gtk_widget_show (bar->separator);
        gtk_widget_show (bar->hide_button);
        gtk_widget_hide (bar->show_button);
    } else {
        gtk_widget_hide (bar->tree_button);
        gtk_widget_hide (bar->places_button);
        gtk_widget_hide (bar->hide_button);
        gtk_widget_hide (bar->separator);
        gtk_widget_show (bar->show_button);
    }

    g_signal_handlers_block_by_func (GTK_BUTTON (bar->tree_button), action_treeview_toggle_callback, bar);
    if (g_strcmp0 (sidebar_id, NEMO_WINDOW_SIDEBAR_TREE) == 0) {
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (bar->tree_button), TRUE);
    } else {
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (bar->tree_button), FALSE);
    }
    g_signal_handlers_unblock_by_func (GTK_BUTTON (bar->tree_button), action_treeview_toggle_callback, bar);


    g_signal_handlers_block_by_func (GTK_BUTTON (bar->places_button), action_places_toggle_callback, bar);

    if (g_strcmp0 (sidebar_id, NEMO_WINDOW_SIDEBAR_PLACES) == 0) {
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (bar->places_button), TRUE);
    } else {
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (bar->places_button), FALSE);
    }
    g_signal_handlers_unblock_by_func (GTK_BUTTON (bar->places_button), action_places_toggle_callback, bar);
}

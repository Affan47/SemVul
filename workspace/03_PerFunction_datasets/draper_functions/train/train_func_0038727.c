columns_setup_popup_menu (GtkTreeViewColumn *column)
{
        GtkWidget *button;

        button = gtk_tree_view_column_get_button (column);
        g_return_if_fail (GTK_IS_WIDGET (button));

        g_signal_connect_swapped (
                button, "button-press-event",
                G_CALLBACK (columns_button_press_event_cb), column);

        g_signal_connect_swapped (
                button, "popup-menu",
                G_CALLBACK (columns_popup_menu_cb), column);
}

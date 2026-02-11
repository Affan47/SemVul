columns_show_popup_menu (GdkEventButton *event,
                         GtkTreeViewColumn *column)
{
        GtkMenu *menu;
        GtkWidget *view;
        const gchar *column_title;
        gchar *label, *tooltip;

        column_title = gtk_tree_view_column_get_title (column);
        view = gtk_tree_view_column_get_tree_view (column);


        g_object_set_data (G_OBJECT (view), "popup-menu-column", column);


        label = g_strdup_printf (
                _("Remove %s Column"), column_title);
        tooltip = g_strdup_printf (
                _("Remove the \"%s\" column from the game list"),
                column_title);
        g_object_set (
                GVA_ACTION_REMOVE_COLUMN, "label",
                label, "tooltip", tooltip, NULL);
        g_free (tooltip);
        g_free (label);

        menu = GTK_MENU (gva_ui_get_managed_widget ("/column-popup"));

        if (event != NULL)
                gtk_menu_popup (
                        menu, NULL, NULL, NULL, NULL,
                        event->button, event->time);
        else
                gtk_menu_popup (
                        menu, NULL, NULL, NULL, NULL,
                        0, gtk_get_current_event_time ());

        return TRUE;
}

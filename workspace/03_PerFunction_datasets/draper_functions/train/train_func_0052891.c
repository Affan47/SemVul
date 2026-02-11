toggle_highlighting (GtkWidget* widget, void* user) {
    gboolean newval = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget));
    GList* tab = gummi->tabmanager->tabs;

    config_set_value ("highlighting", newval? "True": "False");

    while (tab) {
        gtk_source_view_set_highlight_current_line (GTK_SOURCE_VIEW
                (GU_TAB_CONTEXT (tab->data)->editor->view), newval);
        tab = g_list_next (tab);
    }
}

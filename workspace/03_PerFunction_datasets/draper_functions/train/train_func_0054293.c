selection_changed(GtkTreeSelection * selection,
                                  GtkWidget * dialog)
{
    GtkWidget *property_button, *delete_button;

    has_selection = gtk_tree_selection_get_selected(selection, NULL, &iter);

    property_button = g_object_get_data(G_OBJECT(dialog), "property_button");
    delete_button = g_object_get_data(G_OBJECT(dialog), "delete_button");

    if (GTK_WIDGET_IS_SENSITIVE(property_button) != has_selection) {
        gtk_widget_set_sensitive(property_button, has_selection);
        gtk_widget_set_sensitive(delete_button, has_selection);
    }

    return FALSE;
}

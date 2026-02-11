add_separator(GtkWidget *menu) {
    GtkWidget *sep = NULL;
    if (menu) {
        sep = gtk_separator_menu_item_new();
        gtk_widget_show(sep);
        gtk_widget_set_sensitive(sep, TRUE);
        gtk_container_add(GTK_CONTAINER (menu), sep);
    }
    return sep;
}

add_to_menu (GtkWidget * menu, struct Item * item)
{
    GtkWidget * widget = gtk_image_menu_item_new_with_mnemonic (item->name);
    g_object_set_data ((GObject *) widget, "func", (void *) item->func);
    g_signal_connect (widget, "activate", item->func, NULL);

    if (item->icon)
        gtk_image_menu_item_set_image ((GtkImageMenuItem *) widget,
         gtk_image_new_from_stock (item->icon, GTK_ICON_SIZE_MENU));

    gtk_widget_show (widget);
    gtk_menu_shell_append ((GtkMenuShell *) menu, widget);
}

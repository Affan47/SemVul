append_menuitem(GtkWidget *menu, const gchar *text, GCallback callback, gpointer data)
{
    GtkWidget *menu_item;

    menu_item = gtk_menu_item_new_with_mnemonic(text);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item);

    if (callback)
        g_signal_connect(G_OBJECT(menu_item), "activate", callback, data);

    return menu_item;
}

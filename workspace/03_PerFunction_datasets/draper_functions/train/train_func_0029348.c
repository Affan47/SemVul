plugin_register_menu (GModule *handle, gchar *name, gchar *function)
{
    GtkSignalFunc  sig_function;
    GtkWidget *newMenuItem;
    void *temp;
    gpointer *sigptr;


    temp = (void *)&sig_function;
    sigptr = (gpointer *)temp;

    if (!g_module_symbol(handle, function, sigptr))
    {
        g_message (_("Error while registering the menu: %s"), g_module_error());
        return FALSE;
    }

    newMenuItem = gtk_menu_item_new_with_label(name);
    gtk_widget_show(newMenuItem);

    gtk_menu_shell_prepend(GTK_MENU_SHELL(pluginMenu), newMenuItem);

    gtk_signal_connect(GTK_OBJECT(newMenuItem), "activate", sig_function, NULL);

    return TRUE;
}

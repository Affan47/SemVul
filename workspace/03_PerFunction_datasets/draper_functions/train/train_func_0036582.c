mud_tray_popup_menu_cb(GtkStatusIcon *icon, guint button,
                            guint activate_time, MudTray *tray)
{
        static GtkWidget *menu = NULL;
        GtkWidget *entry;

        if (menu) {
                gtk_widget_destroy(menu);
        }

        menu = gtk_menu_new();

        if (tray->priv->window_invisible == FALSE)
                entry = gtk_menu_item_new_with_mnemonic(_("_Hide window"));
        else
                entry = gtk_menu_item_new_with_mnemonic(_("_Show window"));
        g_signal_connect(G_OBJECT(entry), "activate", G_CALLBACK(mud_tray_window_toggle), tray);

        gtk_menu_shell_append(GTK_MENU_SHELL(menu), entry);
	entry = gtk_separator_menu_item_new ();
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), entry);
        entry = gtk_menu_item_new_with_mnemonic(_("_Quit"));
        gtk_menu_shell_append(GTK_MENU_SHELL(menu), entry);
        g_signal_connect(G_OBJECT(entry), "activate", G_CALLBACK(mud_tray_window_exit), tray);

        gtk_widget_show_all(menu);
        gtk_menu_popup(GTK_MENU(menu),
                       NULL, NULL,
                       gtk_status_icon_position_menu, icon,
                       button, activate_time);
}

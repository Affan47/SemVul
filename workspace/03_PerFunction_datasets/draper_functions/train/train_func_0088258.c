log_window_popup_menu_extend(GtkTextView *textview,
   			GtkMenu *menu, LogWindow *logwin)
{
	GtkWidget *menuitem;

	cm_return_if_fail(menu != NULL);
	cm_return_if_fail(GTK_IS_MENU_SHELL(menu));

	menuitem = gtk_separator_menu_item_new();
	gtk_menu_shell_prepend(GTK_MENU_SHELL(menu), menuitem);
	gtk_widget_show(menuitem);

	menuitem = gtk_menu_item_new_with_mnemonic(_("Clear _Log"));
	g_signal_connect(G_OBJECT(menuitem), "activate",
			 G_CALLBACK(log_window_clear), logwin);
	gtk_menu_shell_prepend(GTK_MENU_SHELL(menu), menuitem);
	gtk_widget_show(menuitem);
}

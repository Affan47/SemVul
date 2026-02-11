account_menu(GdkEventButton *event, gpointer d)
{
	GtkWidget *menu;
	eb_account *acc = (eb_account *)d;
	menu_data *md;

	menu = gtk_menu_new();

	gtkut_create_menu_button(GTK_MENU(menu),
		_("Edit Account..."), G_CALLBACK(edit_account_callback), d);

	gtkut_create_menu_button(GTK_MENU(menu),
		_("Delete Account..."),
		G_CALLBACK(offer_remove_account_callback), d);

	gtkut_create_menu_button(GTK_MENU(menu), NULL, NULL, NULL);


	if (CAN(acc, send_file))
		gtkut_create_menu_button(GTK_MENU(menu),
			_("Send File..."), G_CALLBACK(send_file_callback), d);

	gtkut_create_menu_button(GTK_MENU(menu),
		_("Info..."), G_CALLBACK(get_info), d);

	gtkut_create_menu_button(GTK_MENU(menu), NULL, NULL, NULL);


	if ((md = GetPref(EB_CONTACT_MENU))) {
		int should_sep =
			(add_menu_items(menu, -1, 0, NULL, acc, NULL) > 0);

		add_menu_items(menu, acc->service_id, should_sep, NULL, acc,
			NULL);
	}

	gtk_menu_popup(GTK_MENU(menu), NULL, NULL, NULL, NULL, event->button,
		event->time);
}

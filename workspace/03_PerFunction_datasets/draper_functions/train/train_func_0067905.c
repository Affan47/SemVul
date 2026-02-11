menu_quick_item (char *cmd, char *label, GtkWidget * menu, int flags,
					  gpointer userdata, char *icon)
{
	GtkWidget *img, *item;
	char *path;

	if (!label)
		item = gtk_menu_item_new ();
	else
	{
		if (icon)
		{


				item = gtk_image_menu_item_new_with_mnemonic (label);
			img = NULL;
			if (access (icon, R_OK) == 0)
				img = gtk_image_new_from_file (icon);
			else
			{

				path = g_build_filename (get_xdir (), icon, NULL);
				if (access (path, R_OK) == 0)
					img = gtk_image_new_from_file (path);
				else
					img = gtk_image_new_from_stock (icon, GTK_ICON_SIZE_MENU);
				g_free (path);
			}

			if (img)
				gtk_image_menu_item_set_image ((GtkImageMenuItem *)item, img);
		}
		else
		{
			if (flags & XCMENU_MARKUP)
			{
				item = gtk_menu_item_new_with_label ("");
				if (flags & XCMENU_MNEMONIC)
					gtk_label_set_markup_with_mnemonic (GTK_LABEL (GTK_BIN (item)->child), label);
				else
					gtk_label_set_markup (GTK_LABEL (GTK_BIN (item)->child), label);
			} else
			{
				if (flags & XCMENU_MNEMONIC)
					item = gtk_menu_item_new_with_mnemonic (label);
				else
					item = gtk_menu_item_new_with_label (label);
			}
		}
	}
	gtk_menu_shell_append (GTK_MENU_SHELL (menu), item);
	g_object_set_data (G_OBJECT (item), "u", userdata);
	if (cmd)
		g_signal_connect (G_OBJECT (item), "activate",
								G_CALLBACK (popup_menu_cb), cmd);
	if (flags & XCMENU_SHADED)
		gtk_widget_set_sensitive (GTK_WIDGET (item), FALSE);
	gtk_widget_show_all (item);

	return item;
}

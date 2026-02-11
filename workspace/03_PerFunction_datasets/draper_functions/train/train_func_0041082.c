panel_desktop_menu_item_new (gboolean use_image,
			     gboolean in_menubar,
			     gboolean append_lock_logout)
{
	PanelDesktopMenuItem *menuitem;
	char                 *name;
	const char           *icon_name;
#ifdef HAVE_TELEPATHY_GLIB
	PanelSessionManager  *manager;
#endif

	menuitem = g_object_new (PANEL_TYPE_DESKTOP_MENU_ITEM, NULL);

	name = panel_util_get_user_name ();
#ifdef HAVE_TELEPATHY_GLIB
	icon_name = PANEL_ICON_USER_AVAILABLE;
#else
	icon_name = PANEL_ICON_COMPUTER;
#endif


	if (in_menubar) {
		gtk_menu_item_set_label (GTK_MENU_ITEM (menuitem), name);
		menuitem->priv->icon_size = panel_menu_bar_object_icon_get_size ();

		if (use_image) {
			GtkWidget *image;
			image = gtk_image_new_from_icon_name (icon_name,
							      menuitem->priv->icon_size);
			gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (menuitem),
						       image);
		}
	} else {
		menuitem->priv->icon_size = panel_menu_icon_get_size ();

		if (use_image)
			setup_menu_item_with_icon (GTK_WIDGET (menuitem),
						   menuitem->priv->icon_size,
						   icon_name, NULL, NULL,
						   name);
		else
			setup_menuitem (GTK_WIDGET (menuitem),
					GTK_ICON_SIZE_INVALID, NULL,
					name);
	}

#ifdef HAVE_TELEPATHY_GLIB
	if (use_image)
		gtk_image_menu_item_set_always_show_image (GTK_IMAGE_MENU_ITEM (menuitem),
							   TRUE);
#endif

	g_free (name);

	menuitem->priv->menu = panel_desktop_menu_item_create_menu (menuitem,
								    append_lock_logout);
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem),
				   menuitem->priv->menu);

#ifdef HAVE_TELEPATHY_GLIB
	manager = panel_session_manager_get ();

	menuitem->priv->presence_changed_id =
		g_signal_connect (manager,
				  "presence-changed",
				  G_CALLBACK (panel_desktop_menu_item_on_presence_changed),
				  menuitem);

	panel_desktop_menu_item_on_presence_changed (manager,
						     panel_session_manager_get_presence (manager),
						     menuitem);
#endif

	return GTK_WIDGET (menuitem);
}

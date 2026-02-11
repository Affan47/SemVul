go_action_combo_pixmaps_connect_proxy (GtkAction *a, GtkWidget *proxy)
{
	GTK_ACTION_CLASS (combo_pixmaps_parent)->connect_proxy (a, proxy);

	if (GTK_IS_IMAGE_MENU_ITEM (proxy)) {
		GOActionComboPixmaps *paction = (GOActionComboPixmaps *)a;
		const char *stock_id = paction->elements[0].stock_id;
		GdkPixbuf *icon = make_icon (a, stock_id, proxy);
		if (icon) {
			GtkWidget *image = gtk_image_new_from_pixbuf (icon);
			g_object_unref (icon);
			gtk_widget_show (image);
			gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (proxy),
						       image);
		}
	}
}

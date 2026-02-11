menu_layout_cb(GtkWidget *item, gpointer none) {
	tab_layout_config = 2;
	if (GTK_CHECK_MENU_ITEM(item)->active)
		tab_layout_config = 0;

	menu_change_layout();
}

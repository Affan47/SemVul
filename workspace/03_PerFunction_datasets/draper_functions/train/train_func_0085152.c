mainwindow_tags_menu_item_activate_cb(GtkWidget *widget,
						     gpointer data)
{
	gint id = GPOINTER_TO_INT(data);
	gboolean set = gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(widget));
	MainWindow *mainwin;

	mainwin = g_object_get_data(G_OBJECT(widget), "mainwin");
	cm_return_if_fail(mainwin != NULL);


	if (g_object_get_data(G_OBJECT(mainwin->tags_menu),
				"dont_toggle"))
		return;

	if (!set)
		id = -id;
	summary_set_tag(mainwin->summaryview, id, NULL);
}

egg_recent_view_gtk_menu_cb (GtkWidget *menu, gpointer data)
{
	EggRecentViewGtkMenuData *md = (EggRecentViewGtkMenuData *) data;
	EggRecentItem *item;

	g_return_if_fail (md);
	g_return_if_fail (md->item);
	g_return_if_fail (md->view);
	g_return_if_fail (EGG_IS_RECENT_VIEW_GTK (md->view));

	item = md->item;

	egg_recent_item_ref (item);

	g_signal_emit (G_OBJECT(md->view), view_signals[ACTIVATE], 0,
		       item);

	egg_recent_item_unref (item);
}

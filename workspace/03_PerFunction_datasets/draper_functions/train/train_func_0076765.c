egg_recent_view_gtk_set_menu (EggRecentViewGtk *view,
				GtkWidget *menu)
{
	g_return_if_fail (view);
	g_return_if_fail (EGG_IS_RECENT_VIEW_GTK (view));
	g_return_if_fail (menu);

	if (view->menu != NULL)
		g_object_unref (view->menu);

	view->menu = menu;
	g_object_ref (view->menu);
}

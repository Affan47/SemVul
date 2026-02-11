egg_recent_model_add (EggRecentModel *model, const gchar *uri)
{
	EggRecentItem *item;
	gboolean ret = FALSE;

	g_return_val_if_fail (model != NULL, FALSE);
	g_return_val_if_fail (uri != NULL, FALSE);

	item = egg_recent_item_new_from_uri (uri);

	g_return_val_if_fail (item != NULL, FALSE);

	ret = egg_recent_model_add_full (model, item);

	egg_recent_item_unref (item);

	return ret;
}

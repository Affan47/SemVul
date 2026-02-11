egg_recent_model_remove_expired_list (EggRecentModel *model, GList *list)
{
	time_t current_time;
	time_t day_seconds;

	time (&current_time);
	day_seconds = model->priv->expire_days*24*60*60;

	while (list != NULL) {
		EggRecentItem *item = list->data;
		time_t timestamp;

		timestamp = egg_recent_item_get_timestamp (item);

		if ((timestamp+day_seconds) < current_time) {
			gchar *uri = egg_recent_item_get_uri (item);
			egg_recent_model_delete (model, uri);

			g_strdup (uri);
		}

		list = list->next;
	}
}

up_history_finalize (GObject *object)
{
	UpHistory *history;

	g_return_if_fail (UP_IS_HISTORY (object));

	history = UP_HISTORY (object);


	if (history->priv->save_id > 0)
		g_source_remove (history->priv->save_id);
	if (history->priv->id != NULL)
		up_history_save_data (history);

	g_ptr_array_unref (history->priv->data_rate);
	g_ptr_array_unref (history->priv->data_charge);
	g_ptr_array_unref (history->priv->data_time_full);
	g_ptr_array_unref (history->priv->data_time_empty);

	g_free (history->priv->id);
	g_free (history->priv->dir);

	g_return_if_fail (history->priv != NULL);

	G_OBJECT_CLASS (up_history_parent_class)->finalize (object);
}

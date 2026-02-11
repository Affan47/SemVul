save_chapters_result_cb (gpointer	data,
			 gpointer	user_data)
{
	TotemCmmlAsyncData	*adata;
	TotemChaptersPlugin	*plugin;

	g_return_if_fail (data != NULL);

	adata = (TotemCmmlAsyncData *) data;
	plugin = TOTEM_CHAPTERS_PLUGIN (adata->user_data);

	if (G_UNLIKELY (!adata->successful && !g_cancellable_is_cancelled (adata->cancellable))) {
		totem_action_error (plugin->priv->totem, _("Error while writing file with chapters"),
				    adata->error);
		gtk_widget_set_sensitive (plugin->priv->save_button, TRUE);
	}

	g_object_unref (adata->cancellable);
	g_list_foreach (adata->list, (GFunc) totem_cmml_clip_free, NULL);
	g_list_free (adata->list);
	g_free (adata->error);
	g_free (adata);
}

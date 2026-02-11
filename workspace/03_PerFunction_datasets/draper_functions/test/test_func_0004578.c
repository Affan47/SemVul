finish_chapter_edit (GtkCellRendererText	*renderer,
		     gchar			*path,
		     gchar			*new_text,
		     gpointer			user_data)
{
	TotemChaptersPlugin	*plugin;
	GtkTreeModel		*store;
	GtkTreeIter		iter;
	gchar			*time_str, *tip, *new_title, *old_title;
	gint64			_time;

	g_return_if_fail (TOTEM_IS_CHAPTERS_PLUGIN (user_data));
	g_return_if_fail (new_text != NULL);
	g_return_if_fail (path != NULL);

	plugin = TOTEM_CHAPTERS_PLUGIN (user_data);
	store = gtk_tree_view_get_model (GTK_TREE_VIEW (plugin->priv->tree));

	if (G_UNLIKELY (!gtk_tree_model_get_iter_from_string (store, &iter, path)))
		return;

	gtk_tree_model_get (store, &iter,
			    CHAPTERS_TIME_PRIV_COLUMN, &_time,
			    CHAPTERS_TITLE_PRIV_COLUMN, &old_title,
			    -1);

	if (g_strcmp0 (old_title, new_text) == 0) {
		g_free (old_title);
		return;
	}

	time_str = totem_cmml_convert_msecs_to_str (_time);
	new_title = CHAPTER_TITLE (new_text, time_str);
	tip = CHAPTER_TOOLTIP (new_text, time_str);

	gtk_tree_store_set (GTK_TREE_STORE (store), &iter,
			    CHAPTERS_TITLE_COLUMN, new_title,
			    CHAPTERS_TOOLTIP_COLUMN, tip,
			    CHAPTERS_TITLE_PRIV_COLUMN, new_text,
			    -1);

	gtk_widget_set_sensitive (plugin->priv->save_button, TRUE);

	g_free (old_title);
	g_free (new_title);
	g_free (tip);
	g_free (time_str);
}

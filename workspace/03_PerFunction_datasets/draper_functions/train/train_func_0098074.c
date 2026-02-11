nemo_query_editor_changed_force (NemoQueryEditor *editor, gboolean force_reload)
{
	NemoQuery *query;

	if (editor->details->change_frozen) {
		return;
	}

	if (query_is_valid (editor)) {
		query = nemo_query_editor_get_query (editor);
		g_signal_emit (editor, signals[CHANGED], 0,
			       query, force_reload);
		g_object_unref (query);
	}
}

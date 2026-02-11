finalize_categories (void)
{
	if (save_is_pending)
		idle_saver_cb (NULL);

	if (idle_id > 0) {
		g_source_remove (idle_id);
		idle_id = 0;
	}

	if (categories_table != NULL) {
		g_hash_table_destroy (categories_table);
		categories_table = NULL;
	}

	if (listeners != NULL) {
		g_object_unref (listeners);
		listeners = NULL;
	}

	initialized = FALSE;
}

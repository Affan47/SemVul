snippets_db_get_path_at_object (SnippetsDB *snippets_db,
                                GObject *obj)
{


	g_return_val_if_fail (ANJUTA_IS_SNIPPETS_DB (snippets_db), NULL);

	if (ANJUTA_IS_SNIPPET (obj))
		return get_tree_path_for_snippet (snippets_db, ANJUTA_SNIPPET (obj));

	if (ANJUTA_IS_SNIPPETS_GROUP (obj))
		return get_tree_path_for_snippets_group (snippets_db, ANJUTA_SNIPPETS_GROUP (obj));

	g_return_val_if_reached (NULL);
}

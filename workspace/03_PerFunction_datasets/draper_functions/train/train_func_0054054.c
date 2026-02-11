gth_edit_tags_dialog_update_info (GthEditMetadataDialog *base,
				  GList                 *file_list )
{
	GthEditTagsDialog *self = GTH_EDIT_TAGS_DIALOG (base);
	GList             *checked_tags;
	GList             *inconsistent_tags;
	GList             *scan;

	gth_tags_entry_get_tag_list (GTH_TAGS_ENTRY (self->priv->tags_entry),
				     TRUE,
				     &checked_tags,
				     &inconsistent_tags);

	for (scan = file_list; scan; scan = scan->next) {
		GthFileData *file_data = scan->data;
		GList       *new_tags;
		GthMetadata *metadata;
		GHashTable  *old_tags;
		GList       *scan_tags;

		new_tags = _g_string_list_dup (checked_tags);


		metadata = (GthMetadata *) g_file_info_get_attribute_object (file_data->info, "general::tags");
		old_tags = _g_hash_table_from_string_list (gth_metadata_get_string_list (metadata));
		for (scan_tags = inconsistent_tags; scan_tags; scan_tags = scan_tags->next) {
			char *inconsistent_tag = scan_tags->data;

			if (g_hash_table_lookup (old_tags, inconsistent_tag) != NULL)
				new_tags = g_list_prepend (new_tags, g_strdup (inconsistent_tag));
		}
		g_hash_table_unref (old_tags);


		if (new_tags != NULL) {
			GthStringList *file_tags;
			GthMetadata   *metadata;

			new_tags = g_list_sort (new_tags, (GCompareFunc) g_strcmp0);
			file_tags = gth_string_list_new (new_tags);
			metadata = gth_metadata_new_for_string_list (file_tags);
			g_file_info_set_attribute_object (file_data->info, "general::tags", G_OBJECT (metadata));

			g_object_unref (metadata);
			g_object_unref (file_tags);
			_g_string_list_free (new_tags);
		}
		else
			g_file_info_remove_attribute (file_data->info, "general::tags");
	}

	g_list_free (inconsistent_tags);
	_g_string_list_free (checked_tags);
}

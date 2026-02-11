dialog_doc_metadata_get_value_type_from_name (gchar const *name, GType def)
{

	static GHashTable *dialog_doc_metadata_name_to_type = NULL;
	gpointer res;

	if (NULL == dialog_doc_metadata_name_to_type) {
		static struct {
			char const *name;
			GType type;
		} const map [] = {
			{GSF_META_NAME_GENERATOR,            G_TYPE_STRING},
			{GSF_META_NAME_INITIAL_CREATOR,      G_TYPE_STRING},
			{GSF_META_NAME_CREATOR,              G_TYPE_STRING},
			{GSF_META_NAME_TITLE,                G_TYPE_STRING},
			{GSF_META_NAME_SUBJECT,              G_TYPE_STRING},
			{GSF_META_NAME_MANAGER,              G_TYPE_STRING},
			{GSF_META_NAME_COMPANY,              G_TYPE_STRING},
			{GSF_META_NAME_CATEGORY,             G_TYPE_STRING},
			{GSF_META_NAME_DESCRIPTION,          G_TYPE_STRING},
			{GSF_META_NAME_LAST_SAVED_BY,        G_TYPE_STRING},
			{GSF_META_NAME_TEMPLATE,             G_TYPE_STRING},
			{GSF_META_NAME_EDITING_DURATION,     G_TYPE_STRING},
			{GSF_META_NAME_SPREADSHEET_COUNT,    G_TYPE_INT},
			{GSF_META_NAME_TABLE_COUNT,          G_TYPE_INT},
			{GSF_META_NAME_CELL_COUNT,           G_TYPE_INT},
			{GSF_META_NAME_CHARACTER_COUNT,      G_TYPE_INT},
			{GSF_META_NAME_BYTE_COUNT,           G_TYPE_INT},
			{GSF_META_NAME_SECURITY,             G_TYPE_INT},
			{GSF_META_NAME_HIDDEN_SLIDE_COUNT,   G_TYPE_INT},
			{GSF_META_NAME_LINE_COUNT,           G_TYPE_INT},
			{GSF_META_NAME_SLIDE_COUNT,          G_TYPE_INT},
			{GSF_META_NAME_WORD_COUNT,           G_TYPE_INT},
			{GSF_META_NAME_MM_CLIP_COUNT,        G_TYPE_INT},
			{GSF_META_NAME_NOTE_COUNT,           G_TYPE_INT},
			{GSF_META_NAME_PARAGRAPH_COUNT,      G_TYPE_INT},
			{GSF_META_NAME_PAGE_COUNT,           G_TYPE_INT},
			{GSF_META_NAME_CODEPAGE,             G_TYPE_INT},
			{GSF_META_NAME_LOCALE_SYSTEM_DEFAULT,G_TYPE_INT},
			{GSF_META_NAME_OBJECT_COUNT,         G_TYPE_INT},
			{"xlsx:HyperlinksChanged",           G_TYPE_BOOLEAN},
			{GSF_META_NAME_LINKS_DIRTY,          G_TYPE_BOOLEAN},
			{"xlsx:SharedDoc",                   G_TYPE_BOOLEAN},
			{GSF_META_NAME_SCALE,                G_TYPE_BOOLEAN}
		};
		static char const *map_vector[] =
			{GSF_META_NAME_KEYWORDS,
			 GSF_META_NAME_DOCUMENT_PARTS,
			 GSF_META_NAME_HEADING_PAIRS};
		static char const *map_timestamps[] =
			{GSF_META_NAME_DATE_CREATED,
			 GSF_META_NAME_DATE_MODIFIED};


		int i = G_N_ELEMENTS (map);
		dialog_doc_metadata_name_to_type = g_hash_table_new (g_str_hash, g_str_equal);
		while (i-- > 0)
			g_hash_table_insert (dialog_doc_metadata_name_to_type,
					     (gpointer)map[i].name,
					     GINT_TO_POINTER (map[i].type));

		i = G_N_ELEMENTS (map_vector);
		while (i-- > 0)
			g_hash_table_insert (dialog_doc_metadata_name_to_type,
					     (gpointer)map_vector[i],
					     GINT_TO_POINTER (GSF_DOCPROP_VECTOR_TYPE));

		i = G_N_ELEMENTS (map_timestamps);
		while (i-- > 0)
			g_hash_table_insert (dialog_doc_metadata_name_to_type,
					     (gpointer)map_timestamps[i],
					     GINT_TO_POINTER (GSF_TIMESTAMP_TYPE));

	}

	res = g_hash_table_lookup (dialog_doc_metadata_name_to_type, name);

	if (res != NULL)
		return GPOINTER_TO_INT (res);
	else
		return def;
}

load_tree (GtkTreeStore           *store,
	   glMerge                *merge)
{
	const GList   *record_list;
	GList         *p_rec, *p_field;
	glMergeRecord *record;
	glMergeField  *field;
	GtkTreeIter    iter1, iter2;
	gchar         *primary_key;
	gchar         *primary_value;

	gl_debug (DEBUG_MERGE, "START");

	gtk_tree_store_clear (store);

	primary_key = gl_merge_get_primary_key (merge);
	record_list = gl_merge_get_record_list (merge);

	for ( p_rec=(GList *)record_list; p_rec!=NULL; p_rec=p_rec->next ) {
		record = (glMergeRecord *)p_rec->data;

		primary_value = gl_merge_eval_key (record, primary_key);

		gtk_tree_store_append (store, &iter1, NULL);
		gtk_tree_store_set (store, &iter1,
				    SELECT_COLUMN,       record->select_flag,
				    RECORD_FIELD_COLUMN, primary_value,
				    IS_RECORD_COLUMN,    TRUE,
				    DATA_COLUMN,         record,
				    -1);

		g_free (primary_value);

		for ( p_field=record->field_list; p_field!=NULL; p_field=p_field->next ) {
			field = (glMergeField *)p_field->data;

			gtk_tree_store_append (store, &iter2, &iter1);
			gtk_tree_store_set (store, &iter2,
					    RECORD_FIELD_COLUMN, field->key,
					    VALUE_COLUMN,        field->value,
					    IS_RECORD_COLUMN,    FALSE,
					    -1);
		}
	}

	g_free (primary_key);

	gl_debug (DEBUG_MERGE, "END");
}

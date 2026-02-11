_utility_data_model_to_nodeset (GdaDataModel * model,
				xmlXPathObjectPtr * nodeset, GError ** error)
{
	gint nrows, i;
	gint *rcols, rnb_cols;
	gchar **col_ids = NULL;
	gint c;

	xmlNodePtr mainnode;
	mainnode = xmlNewNode (NULL, (xmlChar *) "resultset");
	if (mainnode == NULL) {
#ifdef GDA_DEBUG_NO
		g_print ("xmlNewNode return NULL\n");
#endif
		g_set_error (error, 0, 0, "%s", "xmlNewNode return NULL\n");
		return -1;
	}

	rnb_cols = gda_data_model_get_n_columns (model);
	rcols = g_new (gint, rnb_cols);
	for (i = 0; i < rnb_cols; i++)
		rcols[i] = i;

	col_ids = g_new0 (gchar *, rnb_cols);
	for (c = 0; c < rnb_cols; c++) {
		GdaColumn *column;
		const gchar *name;
		column = gda_data_model_describe_column (model, rcols[c]);
		name = gda_column_get_name (column);
		if (name)
			col_ids[c] = g_strdup (name);
		else
			col_ids[c] = g_strdup_printf ("_%d", c);
	}


	nrows = gda_data_model_get_n_rows (model);
	if (nrows > 0) {
		xmlNodePtr row, field;
		gint r, c;
		for (r = 0; r < nrows; r++) {
			row = xmlNewChild (mainnode, NULL, (xmlChar *) "row", NULL);
			for (c = 0; c < rnb_cols; c++) {
				GValue *value;
				xmlChar *str = NULL;
				gboolean isnull = FALSE;

				value = (GValue *) gda_data_model_get_value_at (model, rcols[c], r, error);
				if (!value) {
					for (c = 0; c < rnb_cols; c++)
						g_free (col_ids[c]);
					g_free (col_ids);
					g_free (rcols);
					return -1;
				}
				if (gda_value_is_null ((GValue *) value))
					isnull = TRUE;
				else
					str = value_to_xmlchar (value);
				field = xmlNewTextChild (row, NULL, (xmlChar *) "column", (xmlChar *) str);
				xmlSetProp (field, (xmlChar *) "name", (xmlChar *) col_ids[c]);
				if (isnull)
					xmlSetProp (field, (xmlChar *) "isnull", (xmlChar *) "true");
				g_free (str);
			}
		}
	}
	for (c = 0; c < rnb_cols; c++)
		g_free (col_ids[c]);
	g_free (col_ids);
	g_free (rcols);

	*nodeset = (xmlXPathObjectPtr) xmlXPathNewNodeSet (mainnode);

	return 0;
}

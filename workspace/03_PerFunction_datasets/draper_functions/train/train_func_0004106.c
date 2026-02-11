find_row_in_model (GdaDataModel *find_in, GdaDataModel *data, gint row, gint *pk_cols, gint pk_cols_nb,
		   gboolean *out_has_changed, GError **error)
{
	gint i, erow;
	GSList *values = NULL;

	for (i = 0; i < pk_cols_nb; i++) {
		const GValue *cvalue;
		cvalue = gda_data_model_get_value_at (data, pk_cols[i], row, error);
		if (!cvalue)
			return -2;
		values = g_slist_append (values, (gpointer) cvalue);
	}
	erow = gda_data_model_get_row_from_values (find_in, values, pk_cols);
	g_slist_free (values);

	if (erow >= 0) {
		gint ncols;
		ncols = gda_data_model_get_n_columns (find_in);
		if (ncols > gda_data_model_get_n_columns (data)) {
			g_set_error (error, GDA_META_STORE_ERROR, GDA_META_STORE_MODIFY_CONTENTS_ERROR,
				"%s", _("Data models should have the same number of columns"));
			erow = -2;
		}
		else {
			gboolean changed = FALSE;
			for (i = 0; i < ncols; i++) {
				const GValue *v1, *v2;
				v1 = gda_data_model_get_value_at (find_in, i, erow, error);
				if (!v1)
					return -2;
				v2 = gda_data_model_get_value_at (data, i, row, error);
				if (!v2)
					return -2;
				if (gda_value_compare (v1, v2)) {
					changed = TRUE;
					break;
				}
			}
			*out_has_changed = changed;
		}
	}

	return erow;
}

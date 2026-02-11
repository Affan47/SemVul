data_model_errors_remove_row (GdaDataModel *model, gint row, GError **error)
{
	DataModelErrors *imodel;

	g_return_val_if_fail (IS_DATA_MODEL_ERRORS (model), FALSE);
	imodel = (DataModelErrors *) model;
	g_return_val_if_fail (imodel->priv, FALSE);

	if (row >= (gint)imodel->priv->rows->len) {
		gchar *str;
		if (imodel->priv->rows->len > 0)
			str = g_strdup_printf ("Row %d out of range (0-%d)", row,
					       imodel->priv->rows->len - 1);
		else
			str = g_strdup_printf ("Row %d not found (empty data model)", row);
		g_set_error (error, TEST_ERROR, TEST_ERROR_GENERIC, "%s", str);
		g_free (str);
                return FALSE;
        }

	GdaRow *drow;
	drow =  g_ptr_array_index (imodel->priv->rows, row);

	g_object_unref (drow);
	g_ptr_array_remove_index (imodel->priv->rows, row);
	gda_data_model_row_removed (model, row);

	return TRUE;
}

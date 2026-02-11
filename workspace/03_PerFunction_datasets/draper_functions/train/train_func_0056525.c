gda_data_model_dir_dispose (GObject * object)
{
	GdaDataModelDir *model = (GdaDataModelDir *) object;

	g_return_if_fail (GDA_IS_DATA_MODEL_DIR (model));

	if (model->priv) {
		if (model->priv->tmp_value) {
			gda_value_free (model->priv->tmp_value);
			model->priv->tmp_value = NULL;
		}

		if (model->priv->basedir) {
			g_free (model->priv->basedir);
			model->priv->basedir = NULL;
		}

		if (model->priv->errors) {
                        g_slist_foreach (model->priv->errors, (GFunc) g_error_free, NULL);
                        g_slist_free (model->priv->errors);
                }

		if (model->priv->columns) {
                        g_slist_foreach (model->priv->columns, (GFunc) g_object_unref, NULL);
                        g_slist_free (model->priv->columns);
                        model->priv->columns = NULL;
                }

		g_ptr_array_foreach (model->priv->rows, (GFunc) file_row_foreach_func, NULL);
		g_ptr_array_free (model->priv->rows, TRUE);
		g_free (model->priv);
		model->priv = NULL;
	}

	parent_class->dispose (object);
}

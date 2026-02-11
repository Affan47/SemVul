gda_data_meta_wrapper_dispose (GObject *object)
{
	GdaDataMetaWrapper *model = (GdaDataMetaWrapper *) object;

	g_return_if_fail (GDA_IS_DATA_META_WRAPPER (model));


	if (model->priv) {

		if (model->priv->model) {
			g_object_unref (model->priv->model);
			model->priv->model = NULL;
		}

		if (model->priv->computed_rows) {
			g_hash_table_destroy (model->priv->computed_rows);
			model->priv->computed_rows = NULL;
		}

		if (model->priv->buffer) {
			comp_row_free (model->priv->buffer);
			model->priv->buffer = NULL;
		}

		if (model->priv->cols_to_wrap) {
			g_free (model->priv->cols_to_wrap);
			model->priv->cols_to_wrap = NULL;
			model->priv->cols_to_wrap_size = 0;
		}
	}


	parent_class->dispose (object);
}

gda_holder_dispose (GObject *object)
{
	GdaHolder *holder;

	holder = GDA_HOLDER (object);
	if (holder->priv) {
		gda_holder_set_bind (holder, NULL, NULL);
		gda_holder_set_full_bind (holder, NULL);

		if (holder->priv->source_model) {
			g_object_unref (holder->priv->source_model);
			holder->priv->source_model = NULL;
		}

		holder->priv->g_type = G_TYPE_INVALID;

		if (holder->priv->value) {
			if (holder->priv->is_freeable)
				gda_value_free (holder->priv->value);
			holder->priv->value = NULL;
		}

		if (holder->priv->default_value) {
			gda_value_free (holder->priv->default_value);
			holder->priv->default_value = NULL;
		}

		if (holder->priv->invalid_error) {
			g_error_free (holder->priv->invalid_error);
			holder->priv->invalid_error = NULL;
		}
	}


	parent_class->dispose (object);
}

search_bar_dispose (GObject *object)
{
	ESearchBarPrivate *priv;

	priv = E_SEARCH_BAR_GET_PRIVATE (object);

	if (priv->web_view != NULL) {
		g_object_unref (priv->web_view);
		priv->web_view = NULL;
	}

	if (priv->entry != NULL) {
		g_object_unref (priv->entry);
		priv->entry = NULL;
	}

	if (priv->case_sensitive_button != NULL) {
		g_object_unref (priv->case_sensitive_button);
		priv->case_sensitive_button = NULL;
	}

	if (priv->prev_button != NULL) {
		g_object_unref (priv->prev_button);
		priv->prev_button = NULL;
	}

	if (priv->next_button != NULL) {
		g_object_unref (priv->next_button);
		priv->next_button = NULL;
	}

	if (priv->wrapped_next_box != NULL) {
		g_object_unref (priv->wrapped_next_box);
		priv->wrapped_next_box = NULL;
	}

	if (priv->wrapped_prev_box != NULL) {
		g_object_unref (priv->wrapped_prev_box);
		priv->wrapped_prev_box = NULL;
	}

	if (priv->matches_label != NULL) {
		g_object_unref (priv->matches_label);
		priv->matches_label = NULL;
	}


	G_OBJECT_CLASS (e_search_bar_parent_class)->dispose (object);
}

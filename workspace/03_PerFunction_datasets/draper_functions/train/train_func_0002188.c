gth_search_finalize (GObject *object)
{
	GthSearch *search;

	search = GTH_SEARCH (object);

	if (search->priv != NULL) {
		if (search->priv->folder != NULL)
			g_object_unref (search->priv->folder);
		if (search->priv->test != NULL)
			g_object_unref (search->priv->test);
		g_free (search->priv);
		search->priv = NULL;
	}

	G_OBJECT_CLASS (gth_search_parent_class)->finalize (object);
}

_set_uri (CcBackgroundItem *item,
	  const char       *value)
{
        g_free (item->priv->uri);
        if (value && *value == '\0') {
		item->priv->uri = NULL;
	} else {
		if (value && strstr (value, "://") == NULL)
			g_warning ("URI '%s' is invalid", value);
		item->priv->uri = g_strdup (value);
	}
}

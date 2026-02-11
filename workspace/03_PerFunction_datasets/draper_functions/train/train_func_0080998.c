git_cat_file_set_property (GObject      *object,
			    guint         param_id,
			    const GValue *value,
			    GParamSpec   *pspec)
{
	GiggleGitCatFilePriv *priv;

	priv = GET_PRIV (object);

	switch (param_id) {
	case PROP_TYPE:
		g_assert (NULL == priv->type);
		priv->type = g_value_dup_string (value);
		break;

	case PROP_SHA:
		g_assert (NULL == priv->sha);
		priv->sha = g_value_dup_string (value);
		break;

	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, param_id, pspec);
		break;
	}
}

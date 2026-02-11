git_get_property (GObject    *object,
		  guint       param_id,
		  GValue     *value,
		  GParamSpec *pspec)
{
	GiggleGitPriv *priv;

	priv = GIGGLE_GIT (object)->priv;

	switch (param_id) {
	case PROP_DESCRIPTION:
		g_value_set_string (value, priv->description);
		break;
	case PROP_DIRECTORY:
		g_value_set_string (value, priv->directory);
		break;
	case PROP_GIT_DIR:
		g_value_set_string (value, priv->git_dir);
		break;
	case PROP_PROJECT_DIR:
		g_value_set_string (value, priv->project_dir);
		break;
	case PROP_PROJECT_NAME:
		g_value_set_string (value, priv->project_name);
		break;
	case PROP_REMOTES:
		g_value_set_pointer (value, priv->remotes);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, param_id, pspec);
		break;
	}
}

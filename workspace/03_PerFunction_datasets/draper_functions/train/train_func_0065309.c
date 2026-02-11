gitg_repository_set_property (GObject      *object,
                              guint         prop_id,
                              GValue const *value,
                              GParamSpec   *pspec)
{
	GitgRepository *self = GITG_REPOSITORY (object);

	switch (prop_id)
	{
		case PROP_WORK_TREE:
			if (self->priv->work_tree)
			{
				g_object_unref (self->priv->work_tree);
			}

			self->priv->work_tree = g_value_dup_object (value);
		break;
		case PROP_GIT_DIR:
			if (self->priv->git_dir)
			{
				g_object_unref (self->priv->git_dir);
			}

			self->priv->git_dir = g_value_dup_object (value);
		break;
		case PROP_SHOW_STAGED:
			self->priv->show_staged = g_value_get_boolean (value);
			gitg_repository_reload (self);
		break;
		case PROP_SHOW_UNSTAGED:
			self->priv->show_unstaged = g_value_get_boolean (value);
			gitg_repository_reload (self);
		break;
		case PROP_SHOW_STASH:
			self->priv->show_stash = g_value_get_boolean (value);
			gitg_repository_reload (self);
		break;
		case PROP_TOPO_ORDER:
			self->priv->topoorder = g_value_get_boolean (value);

			if (self->priv->selection != NULL)
			{
				build_log_args (self,
					        g_strv_length (self->priv->selection),
					        (gchar const **)self->priv->selection);
			}

			gitg_repository_reload (self);
		break;
		case PROP_INACTIVE_MAX:
			g_object_set_property (G_OBJECT (self->priv->lanes),
			                      "inactive-max",
			                      value);
			prepare_relane (self);
		break;
		case PROP_INACTIVE_COLLAPSE:
			g_object_set_property (G_OBJECT (self->priv->lanes),
			                      "inactive-collapse",
			                      value);
			prepare_relane (self);
		break;
		case PROP_INACTIVE_GAP:
			g_object_set_property (G_OBJECT (self->priv->lanes),
			                      "inactive-gap",
			                      value);
			prepare_relane (self);
		break;
		case PROP_INACTIVE_ENABLED:
			g_object_set_property (G_OBJECT (self->priv->lanes),
			                      "inactive-enabled",
			                      value);
			prepare_relane (self);
		break;
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

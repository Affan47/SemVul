ao_tasks_set_property(GObject *object, guint prop_id,
								  const GValue *value, GParamSpec *pspec)
{
	AoTasksPrivate *priv = AO_TASKS_GET_PRIVATE(object);

	switch (prop_id)
	{
		case PROP_ENABLE_TASKS:
		{
			gboolean new_val = g_value_get_boolean(value);
			if (new_val && ! priv->enable_tasks)
				ao_tasks_show(AO_TASKS(object));
			if (! new_val && priv->enable_tasks)
				ao_tasks_hide(AO_TASKS(object));

			priv->enable_tasks = new_val;
			if (priv->enable_tasks && main_is_realized() && ! priv->active)
				ao_tasks_set_active(AO_TASKS(object));
			break;
		}
		case PROP_SCAN_ALL_DOCUMENTS:
		{
			priv->scan_all_documents = g_value_get_boolean(value);
			break;
		}
		case PROP_TOKENS:
		{
			const gchar *t = g_value_get_string(value);
			if (! NZV(t))
				t = "TODO;FIXME";
			g_strfreev(priv->tokens);
			priv->tokens = g_strsplit(t, ";", -1);
			ao_tasks_update(AO_TASKS(object), NULL);
			break;
		}
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
			break;
	}
}

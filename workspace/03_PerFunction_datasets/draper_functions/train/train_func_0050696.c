egg_recent_model_limit_changed (GConfClient *client, guint cnxn_id,
				GConfEntry *entry, gpointer user_data)
{
	EggRecentModel *model;
	GConfValue *value;

	model = EGG_RECENT_MODEL (user_data);

	g_return_if_fail (model != NULL);

	if (model->priv->use_default_limit == FALSE)
		return;


	if (entry == NULL)
		return;

	value = gconf_entry_get_value (entry);

	if (value->type != GCONF_VALUE_INT) {
		g_warning ("Expected GConfValue of type integer, "
			   "got something else");
	}


	egg_recent_model_set_limit_internal (model, gconf_value_get_int (value));
}

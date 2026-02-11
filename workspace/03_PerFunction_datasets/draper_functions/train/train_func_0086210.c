egg_recent_model_init (EggRecentModel * model)
{
	if (!gnome_vfs_init ()) {
		g_warning ("gnome-vfs initialization failed.");
		return;
	}


	model->priv = g_new0 (EggRecentModelPrivate, 1);

	model->priv->path = g_strdup_printf ("%s" EGG_RECENT_MODEL_FILE_PATH,
					     g_get_home_dir ());

	model->priv->mime_filter_values   = NULL;
	model->priv->group_filter_values  = NULL;
	model->priv->scheme_filter_values = NULL;

	model->priv->client = gconf_client_get_default ();
	gconf_client_add_dir (model->priv->client, EGG_RECENT_MODEL_KEY_DIR,
			      GCONF_CLIENT_PRELOAD_ONELEVEL, NULL);

	model->priv->limit_change_notify_id =
			gconf_client_notify_add (model->priv->client,
						 EGG_RECENT_MODEL_DEFAULT_LIMIT_KEY,
						 egg_recent_model_limit_changed,
						 model, NULL, NULL);

	model->priv->expiration_change_notify_id =
			gconf_client_notify_add (model->priv->client,
						 EGG_RECENT_MODEL_EXPIRE_KEY,
						 egg_recent_model_expiration_changed,
						 model, NULL, NULL);

	model->priv->expire_days = gconf_client_get_int (
					model->priv->client,
					EGG_RECENT_MODEL_EXPIRE_KEY,
					NULL);

#if 0

	model->priv->limit = gconf_client_get_int (
					model->priv->client,
					EGG_RECENT_MODEL_DEFAULT_LIMIT_KEY, NULL);
	model->priv->use_default_limit = TRUE;
#endif
	model->priv->limit = EGG_RECENT_MODEL_DEFAULT_LIMIT;
	model->priv->use_default_limit = FALSE;

	model->priv->monitors = g_hash_table_new_full (
					g_str_hash, g_str_equal,
					(GDestroyNotify) g_free,
					(GDestroyNotify) gnome_vfs_monitor_cancel);

	model->priv->monitor = NULL;
	egg_recent_model_monitor (model, TRUE);
}

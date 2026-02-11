gm_world_auto_login(GmWorld *world) {
	gchar const *player_name = gm_options_get(world->priv->options,
			"player_name");
	gchar const *passwd = gm_options_get(world->priv->options, "password");
	gchar *sendln;

	if (player_name && *player_name != '\0') {
		sendln = g_strconcat("connect ", player_name, " ", passwd, NULL);
		gm_world_sendln_log(world, sendln, LOG_NONE);
		g_free(sendln);
	}
}

gm_mcp_icecrew_userlist_process_state_changed(GmMcpIcecrewUserlist *userlist,
		GmPlayerdbPlayerInfo *ppi, gchar const *value, gchar const *old) {
	gboolean was_away, was_idle;
	gboolean is_away, is_idle;
	gchar const *name = gm_playerdb_player_info_get_prop(ppi,
			userlist->priv->property_names[P_NAME]);

	was_away = (strstr(old, "away") != NULL || strstr(old, "busy") != NULL);
	was_idle = (strstr(old, "idle") != NULL);

	is_away = (strstr(value, "away") != NULL || strstr(value, "busy") != NULL);
	is_idle = (strstr(value, "idle") != NULL);

	if (was_away && !is_away) {
		gm_mcp_icecrew_userlist_process_triggers(userlist, name,
				TCT_USER_AWAY_OFF);
	} else if (!was_away && is_away) {
		gm_mcp_icecrew_userlist_process_triggers(userlist, name,
				TCT_USER_AWAY);
	}

	if (was_idle && !is_idle) {
		gm_mcp_icecrew_userlist_process_triggers(userlist, name,
				TCT_USER_IDLE_OFF);
	} else if (!was_idle && is_idle) {
		gm_mcp_icecrew_userlist_process_triggers(userlist, name,
				TCT_USER_IDLE);
	}
}

get_done_cb (NMSecretAgent *agent,
             gconstpointer call_id,
             GHashTable *secrets,
             GError *error,
             gpointer user_data)
{
	Request *req = user_data;
	GHashTable *setting_secrets;
	const char *agent_dbus_owner;
	gboolean agent_has_modify;
	struct passwd *pw;
	char *agent_uname = NULL;

	g_return_if_fail (call_id == req->current_call_id);

	agent_has_modify = req->current_has_modify;
	req->current_has_modify = FALSE;
	req->current = NULL;
	req->current_call_id = NULL;

	if (error) {
		nm_log_dbg (LOGD_AGENTS, "(%s) agent failed secrets request %p/%s: (%d) %s",
		            nm_secret_agent_get_description (agent),
		            req, req->setting_name,
		            error ? error->code : -1,
		            (error && error->message) ? error->message : "(unknown)");


		req->next_callback (req);
		return;
	}


	setting_secrets = g_hash_table_lookup (secrets, req->setting_name);
	if (!setting_secrets || !g_hash_table_size (setting_secrets)) {
		nm_log_dbg (LOGD_AGENTS, "(%s) agent returned no secrets for request %p/%s",
		            nm_secret_agent_get_description (agent),
		            req, req->setting_name);


		req->next_callback (req);
		return;
	}

	nm_log_dbg (LOGD_AGENTS, "(%s) agent returned secrets for request %p/%s",
	            nm_secret_agent_get_description (agent),
	            req, req->setting_name);


	pw = getpwuid (nm_secret_agent_get_owner_uid (agent));
	if (pw && strlen (pw->pw_name)) {

		if (g_utf8_validate (pw->pw_name, -1, NULL))
			agent_uname = g_strdup (pw->pw_name);
	}

	agent_dbus_owner = nm_secret_agent_get_dbus_owner (agent);
	req_complete_success (req, secrets, agent_dbus_owner, agent_uname, agent_has_modify);
	g_free (agent_uname);
}

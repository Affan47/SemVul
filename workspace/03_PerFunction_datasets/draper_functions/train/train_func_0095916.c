get_secrets_cb (AppletAgent *self,
                GHashTable *secrets,
                GError *error,
                gpointer user_data)
{
	Request *r = user_data;


	if (error) {
		g_warn_if_fail (secrets == NULL);
		secrets = NULL;
	}

	if (!g_cancellable_is_cancelled (r->cancellable)) {


		if (secrets && (r->flags != NM_SECRET_AGENT_GET_SECRETS_FLAG_NONE)) {
			NMConnection *dupl;
			GHashTableIter iter;
			const char *setting_name;


			dupl = nm_connection_duplicate (r->connection);
			g_hash_table_iter_init (&iter, secrets);
			while (g_hash_table_iter_next (&iter, (gpointer) &setting_name, NULL))
				nm_connection_update_secrets (dupl, setting_name, secrets, NULL);


			nm_secret_agent_save_secrets (NM_SECRET_AGENT (self), dupl, get_save_cb, NULL);
			g_object_unref (dupl);
		}

		r->get_callback (NM_SECRET_AGENT (r->agent), r->connection, secrets, error, r->callback_data);
	}
	request_free (r);
}

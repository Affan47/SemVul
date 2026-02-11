store_session_specific (CK_SESSION_HANDLE handle, CK_OBJECT_HANDLE key)
{
	Session *sess;

	G_LOCK (wrap_layer);

		if (wrap_sessions) {
			sess = g_hash_table_lookup (wrap_sessions, GINT_TO_POINTER ((gint)handle));
			if (sess == NULL)
				g_warning ("sessions out of sync with lower layer");
			else
				sess->specific = key;
		}

	G_UNLOCK (wrap_layer);
}

on_open_session_plain (GkrOperation *op, DBusMessage *reply, gpointer user_data)
{
	GkrSession *session;
	const char *path;

	if (gkr_operation_handle_errors (op, reply))
		return;


	if (!decode_open_session_plain (reply, &path)) {
		g_message ("received an invalid response to Service.OpenSession()");
		gkr_operation_complete (op, GNOME_KEYRING_RESULT_IO_ERROR);
		return;
	}

	session = session_new ();
	session->path = g_strdup (path);
	session->key = NULL;
	session->n_key = 0;

	G_LOCK (session_globals);
	{
		if (the_session)
			gkr_session_unref (the_session);
		the_session = gkr_session_ref (session);
	}
	G_UNLOCK (session_globals);

	gkr_callback_invoke_op_session (gkr_operation_pop (op), session);
	gkr_session_unref (session);
}

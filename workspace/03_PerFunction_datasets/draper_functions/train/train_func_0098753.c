gkr_session_negotiate (GkrOperation *op)
{
	GkrSession *session = NULL;

	G_LOCK(session_globals);
	{
		if (the_session)
			session = gkr_session_ref (the_session);
	}
	G_UNLOCK(session_globals);


	if (session) {
		gkr_callback_invoke_op_session (gkr_operation_pop (op), session);
		gkr_session_unref (session);
		return;
	}


	session_negotiate_aes (op);
}

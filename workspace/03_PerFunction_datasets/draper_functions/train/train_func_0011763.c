pop3_session_destroy(Session *session)
{
	Pop3Session *pop3_session = POP3_SESSION(session);
	gint n;

	cm_return_if_fail(session != NULL);

	for (n = 1; n <= pop3_session->count; n++)
		g_free(pop3_session->msg[n].uidl);
	g_free(pop3_session->msg);

	if (pop3_session->uidl_table) {
		hash_free_strings(pop3_session->uidl_table);
		g_hash_table_destroy(pop3_session->uidl_table);
	}

	if (pop3_session->partial_recv_table) {
		hash_free_strings(pop3_session->partial_recv_table);
		g_hash_table_destroy(pop3_session->partial_recv_table);
	}

	g_free(pop3_session->greeting);
	g_free(pop3_session->user);
	g_free(pop3_session->pass);
	g_free(pop3_session->error_msg);
}

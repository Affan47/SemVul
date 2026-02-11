gkm_mock_C_CloseSession (CK_SESSION_HANDLE hSession)
{
	Session *session;

	session = g_hash_table_lookup (the_sessions, GUINT_TO_POINTER (hSession));
	g_assert (session != NULL && "No such session found");
	if (!session)
		return CKR_SESSION_HANDLE_INVALID;

	g_hash_table_remove (the_sessions, GUINT_TO_POINTER (hSession));
	return CKR_OK;
}

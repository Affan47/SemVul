acquire_from_credential (GkmCredential *cred, GkmObject *object, gpointer user_data)
{
	GkmSexp **result = user_data;

	g_assert (result);
	g_assert (!*result);


	*result = gkm_credential_pop_data (cred, GKM_BOXED_SEXP);
	if (*result != NULL)
		return TRUE;

	return FALSE;
}

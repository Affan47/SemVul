find_credential (GkmCredential *cred, GkmObject *object, gpointer user_data)
{
	CK_OBJECT_HANDLE *result = user_data;
	g_return_val_if_fail (!*result, FALSE);
	*result = gkm_object_get_handle (GKM_OBJECT (cred));
	return TRUE;
}

test_load_unlock_encrypted (Test *test, gconstpointer unused)
{
	GkmCredential *cred;
	GkmSecretData *sdata;
	GkmDataResult res;
	CK_RV rv;

	gkm_secret_collection_set_filename (test->collection, SRCDIR "/files/encrypted.keyring");


	res = gkm_secret_collection_load (test->collection);
	g_assert (res == GKM_DATA_SUCCESS);


	rv = gkm_credential_create (test->module, gkm_session_get_manager (test->session), GKM_OBJECT (test->collection),
	                            (guchar*)"my-keyring-password", 19, &cred);
	g_assert (rv == CKR_OK);
	gkm_session_add_session_object (test->session, NULL, GKM_OBJECT (cred));
	g_object_unref (cred);

	sdata = gkm_secret_collection_unlocked_use (test->collection, test->session);
	g_assert (sdata != NULL && GKM_IS_SECRET_DATA (sdata));
	test_secret_collection_validate (test->collection, sdata);
	g_object_unref (sdata);
}

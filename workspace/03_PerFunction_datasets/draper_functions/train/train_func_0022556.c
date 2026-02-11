test_module_file_remove (Test *test, gconstpointer unused)
{
	CK_OBJECT_HANDLE objects[256];
	CK_ULONG n_objects;
	CK_ULONG n_check;
	CK_RV rv;

	rv = gkm_session_C_FindObjectsInit (test->session, NULL, 0);
	gkm_assert_cmprv (rv, ==, CKR_OK);
	rv = gkm_session_C_FindObjects (test->session, objects, G_N_ELEMENTS (objects), &n_objects);
	gkm_assert_cmprv (rv, ==, CKR_OK);
	rv = gkm_session_C_FindObjectsFinal (test->session);
	gkm_assert_cmprv (rv, ==, CKR_OK);

	gkm_assert_cmpulong (n_objects, >, 0);


	mock_xdg_module_remove_file ("test-refer-1.trust");

	rv = gkm_session_C_FindObjectsInit (test->session, NULL, 0);
	gkm_assert_cmprv (rv, ==, CKR_OK);
	rv = gkm_session_C_FindObjects (test->session, objects, G_N_ELEMENTS (objects), &n_check);
	gkm_assert_cmprv (rv, ==, CKR_OK);
	rv = gkm_session_C_FindObjectsFinal (test->session);
	gkm_assert_cmprv (rv, ==, CKR_OK);


	gkm_assert_cmpulong (n_check, <, n_objects);
}

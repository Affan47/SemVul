test_module_file_becomes_invalid (Test *test, gconstpointer unused)
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


	mock_xdg_module_empty_file ("test-refer-1.trust");
	mock_xdg_module_touch_file ("test-refer-1.trust", 2);

	rv = gkm_session_C_FindObjectsInit (test->session, NULL, 0);
	gkm_assert_cmprv (rv, ==, CKR_OK);
	rv = gkm_session_C_FindObjects (test->session, objects, G_N_ELEMENTS (objects), &n_check);
	gkm_assert_cmprv (rv, ==, CKR_OK);
	rv = gkm_session_C_FindObjectsFinal (test->session);
	gkm_assert_cmprv (rv, ==, CKR_OK);


	gkm_assert_cmpulong (n_check, <, n_objects);
}

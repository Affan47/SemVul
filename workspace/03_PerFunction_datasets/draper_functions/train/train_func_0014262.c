mock_secret_C_Initialize (CK_VOID_PTR pInitArgs)
{
	GArray *attrs;
	CK_RV rv;

	rv = gkm_mock_C_Initialize (pInitArgs);
	if (rv != CKR_OK)
		return rv;

	attrs = gkm_template_new (NULL, 0);
	gkm_template_set_ulong (attrs, CKA_CLASS, CKO_G_COLLECTION);
	gkm_template_set_boolean (attrs, CKA_G_LOGIN_COLLECTION, CK_TRUE);
	gkm_template_set_string (attrs, CKA_ID, "login");
	gkm_template_set_string (attrs, CKA_LABEL, "Login Keyring");
	gkm_template_set_boolean (attrs, CKA_TRUSTED, CK_TRUE);
	gkm_template_set_boolean (attrs, CKA_G_LOCKED, CK_FALSE);
	gkm_template_set_boolean (attrs, CKA_TOKEN, CK_TRUE);
	gkm_mock_module_take_object (attrs);

	attrs = gkm_template_new (NULL, 0);
	gkm_template_set_ulong (attrs, CKA_CLASS, CKO_G_COLLECTION);
	gkm_template_set_boolean (attrs, CKA_G_LOGIN_COLLECTION, CK_FALSE);
	gkm_template_set_string (attrs, CKA_ID, "other");
	gkm_template_set_string (attrs, CKA_LABEL, "Other Keyring");
	gkm_template_set_boolean (attrs, CKA_TRUSTED, CK_TRUE);
	gkm_template_set_boolean (attrs, CKA_G_LOCKED, CK_TRUE);
	gkm_template_set_boolean (attrs, CKA_TOKEN, CK_TRUE);
	gkm_mock_module_take_object (attrs);

	attrs = gkm_template_new (NULL, 0);
	gkm_template_set_string (attrs, CKA_G_COLLECTION, "login");
	gkm_template_set_string (attrs, CKA_ID, "23");
	gkm_template_set_string (attrs, CKA_LABEL, "Unlock password for: Mock");
	gkm_template_set_ulong (attrs, CKA_CLASS, CKO_SECRET_KEY);
	gkm_template_set_value (attrs, CKA_G_FIELDS, "one\0" "1\0" "two\0" "2\0", 12);
	gkm_template_set_string (attrs, CKA_VALUE, "mock");
	gkm_template_set_boolean (attrs, CKA_TOKEN, CK_TRUE);
	gkm_template_set_boolean (attrs, CKA_G_LOCKED, CK_FALSE);
	gkm_mock_module_take_object (attrs);

	return CKR_OK;
}

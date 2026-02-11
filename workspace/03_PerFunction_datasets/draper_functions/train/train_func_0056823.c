test_create_auto_destruct_not_transient (Test* test, gconstpointer unused)
{
	CK_OBJECT_CLASS klass = CKO_CERTIFICATE;
	CK_CERTIFICATE_TYPE type = CKC_X_509;
	CK_BBOOL transient = CK_FALSE;
	CK_ULONG after = 1;

	CK_ATTRIBUTE attrs[] = {
		{ CKA_G_DESTRUCT_AFTER, &after, sizeof (after) },
		{ CKA_GNOME_TRANSIENT, &transient, sizeof (transient) },
		{ CKA_CLASS, &klass, sizeof (klass) },
		{ CKA_CERTIFICATE_TYPE, &type, sizeof (type) },
		{ CKA_VALUE, test->certificate_data, test->n_certificate_data },
	};

	CK_OBJECT_HANDLE handle;
	CK_RV rv;


	rv = gkm_session_C_CreateObject (test->session, attrs, G_N_ELEMENTS (attrs), &handle);
	g_assert (rv == CKR_TEMPLATE_INCONSISTENT);
}

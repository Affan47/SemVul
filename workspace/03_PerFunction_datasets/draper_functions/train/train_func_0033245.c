test_schema (Test *test, gconstpointer unused)
{
	CK_ATTRIBUTE attr;

	attr.type = CKA_LABEL;
	attr.pValue = "Label";
	attr.ulValueLen = 5;

	gkm_store_register_schema (test->store, &attr, NULL, 0);
	g_assert (gkm_store_lookup_schema (test->store, CKA_LABEL, NULL));


	g_assert (!gkm_store_lookup_schema (test->store, CKA_VALUE, NULL));
}

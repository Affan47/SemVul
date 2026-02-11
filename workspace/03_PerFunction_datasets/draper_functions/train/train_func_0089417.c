test_get_attribute_default (Test *test, gconstpointer unused)
{
	CK_ATTRIBUTE attr;
	CK_RV rv;

	attr.type = CKA_LABEL;
	attr.pValue = NULL;
	rv = gkm_store_get_attribute (test->store, test->object, &attr);
	g_assert (rv == CKR_OK);
	g_assert (attr.ulValueLen == 5);
	attr.pValue = test->buffer;
	rv = gkm_store_get_attribute (test->store, test->object, &attr);
	g_assert (rv == CKR_OK);
	g_assert (attr.ulValueLen == 5);
	g_assert (memcmp (attr.pValue, "label", 5) == 0);
}

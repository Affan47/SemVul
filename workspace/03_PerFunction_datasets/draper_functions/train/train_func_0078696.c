test_set_invalid (Test *test, gconstpointer unused)
{
	CK_ATTRIBUTE attr;

	attr.type = CKA_APPLICATION;
	attr.pValue = "me";
	attr.ulValueLen = 2;

	gkm_store_set_attribute (test->store, test->transaction, test->object, &attr);
	g_assert (gkm_transaction_get_result (test->transaction) == CKR_ATTRIBUTE_TYPE_INVALID);
}

test_set_transaction_default (Test *test, gconstpointer unused)
{
	CK_ATTRIBUTE attr;
	gconstpointer value;
	gsize n_value;


	attr.type = CKA_LABEL;
	attr.pValue = "another";
	attr.ulValueLen = 7;


	gkm_store_set_attribute (test->store, test->transaction, test->object, &attr);
	g_assert (gkm_transaction_get_failed (test->transaction) == FALSE);


	value = gkm_store_read_value (test->store, test->object, CKA_LABEL, &n_value);
	g_assert (value && n_value == attr.ulValueLen);
	g_assert (memcmp (attr.pValue, value, n_value) == 0);


	gkm_transaction_fail (test->transaction, CKR_ATTRIBUTE_VALUE_INVALID);


	value = gkm_store_read_value (test->store, test->object, CKA_LABEL, &n_value);
	g_assert (value && n_value == attr.ulValueLen);
	g_assert (memcmp (attr.pValue, value, n_value) == 0);


	gkm_transaction_complete (test->transaction);
	g_assert (gkm_transaction_get_failed (test->transaction) == TRUE);


	value = gkm_store_read_value (test->store, test->object, CKA_LABEL, &n_value);
	g_assert (value && n_value == 5);
	g_assert (memcmp (value, "label", 5) == 0);
}

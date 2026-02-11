test_read_value_default (Test *test, gconstpointer unused)
{
	gconstpointer value;
	gsize n_value;

	value = gkm_store_read_value (test->store, test->object, CKA_LABEL, &n_value);
	g_assert (value);
	g_assert (n_value == 5);
	g_assert (memcmp (value, "label", 5) == 0);

	value = gkm_store_read_value (test->store, test->object, CKA_BITS_PER_PIXEL, &n_value);
	g_assert (value);
	g_assert (n_value == sizeof (CK_ULONG));
	g_assert (*((CK_ULONG_PTR)value) == 24);
}

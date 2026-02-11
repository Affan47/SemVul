main (int argc, char **argv)
{
	g_test_init (&argc, &argv, NULL);
	g_set_prgname ("test-password");
#if !GLIB_CHECK_VERSION(2,35,0)
	g_type_init ();
#endif

	g_test_add ("/password/lookup-sync", Test, "mock-service-normal.py", setup, test_lookup_sync, teardown);
	g_test_add ("/password/lookup-async", Test, "mock-service-normal.py", setup, test_lookup_async, teardown);
	g_test_add ("/password/lookup-no-name", Test, "mock-service-normal.py", setup, test_lookup_no_name, teardown);

	g_test_add ("/password/store-sync", Test, "mock-service-normal.py", setup, test_store_sync, teardown);
	g_test_add ("/password/store-async", Test, "mock-service-normal.py", setup, test_store_async, teardown);
	g_test_add ("/password/store-unlock", Test, "mock-service-normal.py", setup, test_store_unlock, teardown);

	g_test_add ("/password/delete-sync", Test, "mock-service-delete.py", setup, test_delete_sync, teardown);
	g_test_add ("/password/delete-async", Test, "mock-service-delete.py", setup, test_delete_async, teardown);
	g_test_add ("/password/clear-no-name", Test, "mock-service-delete.py", setup, test_clear_no_name, teardown);

	g_test_add_func ("/password/free-null", test_password_free_null);

	return egg_tests_run_with_loop ();
}

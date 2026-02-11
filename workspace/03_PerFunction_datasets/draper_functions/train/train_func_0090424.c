main (int argc, char **argv)
{
#if !GLIB_CHECK_VERSION(2,35,0)
	g_type_init ();
#endif
	g_test_init (&argc, &argv, NULL);


	g_log_set_handler (G_LOG_DOMAIN, G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG,
	                   null_log_handler, NULL);

	g_test_add ("/xdg-store/module/module_find_twice_is_same", Test, NULL, setup, test_module_find_twice_is_same, teardown);
	g_test_add ("/xdg-store/module/module_file_becomes_invalid", Test, NULL, setup, test_module_file_becomes_invalid, teardown);
	g_test_add ("/xdg-store/module/module_file_remove", Test, NULL, setup, test_module_file_remove, teardown);
	g_test_add ("/xdg-store/module/create_and_add_object", Test, NULL, setup, test_create_and_add_object, teardown);
	g_test_add ("/xdg-store/module/destroy_object", Test, NULL, setup, test_destroy_object, teardown);
	g_test_add ("/xdg-store/module/get_slot_info", Test, NULL, setup, test_get_slot_info, teardown);
	g_test_add ("/xdg-store/module/get_token_info", Test, NULL, setup, test_get_token_info, teardown);

	return egg_tests_run_in_thread_with_loop ();
}

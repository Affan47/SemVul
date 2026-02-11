main(int argc, char **argv) {
	isc_result_t result;

	tries = 2;

	ISC_LIST_INIT(lookup_list);
	ISC_LIST_INIT(server_list);
	ISC_LIST_INIT(search_list);

	fatalexit = 1;
#ifdef WITH_IDN
	idnoptions = IDN_ASCCHECK;
#endif

	debug("main()");
	progname = argv[0];
	pre_parse_args(argc, argv);
	result = isc_app_start();
	check_result(result, "isc_app_start");
	setup_libs();
	setup_system();
	parse_args(ISC_FALSE, argc, argv);
	if (keyfile[0] != 0)
		setup_file_key();
	else if (keysecret[0] != 0)
		setup_text_key();
	result = isc_app_onrun(mctx, global_task, onrun_callback, NULL);
	check_result(result, "isc_app_onrun");
	isc_app_run();
	cancel_all();
	destroy_libs();
	isc_app_finish();
	return ((seen_error == 0) ? 0 : 1);
}

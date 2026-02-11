wi_execv(wi_string_t *program, wi_array_t *arguments) {
	wi_mutable_array_t		*argv;
	const char				**xargv;

	argv = wi_mutable_copy(arguments);

	if(wi_array_count(argv) == 0)
		wi_mutable_array_add_data(argv, program);
	else
		wi_mutable_array_insert_data_at_index(argv, program, 0);

	xargv = wi_array_create_argv(argv);

	if(execv(xargv[0], (char * const *) xargv) < 0) {
		wi_error_set_errno(errno);

		wi_array_destroy_argv(wi_array_count(argv), xargv);
		wi_release(argv);

		return false;
	}

	return true;
}

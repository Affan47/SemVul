exitcode_process(options_t *options_p, int exitcode) {
	int err = _exitcode_process(options_p, exitcode);

	if(err) printf_e("Error: Got error-report from exitcode_process().\nExitcode is %i, strerror(%i) returns \"%s\". However strerror() is not ensures compliance "
			"between exitcode and error description for every utility. So, e.g if you're using rsync, you should look for the error description "
			"into rsync's manpage (\"man 1 rsync\"). Also some advices about diagnostics can be found in clsync's manpage (\"man 1 clsync\", see DIAGNOSTICS)\n",
			exitcode, exitcode, strerror(exitcode));

	return err;
}

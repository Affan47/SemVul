print_trace(int signum)
{

#if (!defined __WIN32__) && (!defined __APPLE_CC__) && (defined HAVE_BACKTRACE)


	backtrace_size = backtrace(backtrace_array, MAX_CALLS_IN_BACKTRACE);

	fprintf(stderr, "print_trace:  Obtained %zd stack frames.\n", backtrace_size);


	backtrace_strings = backtrace_symbols(backtrace_array, backtrace_size);

	fprintf(stderr, "print_trace:  Obtaining symbols now done.\n");

	for (backtrace_counter = 0; backtrace_counter < backtrace_size; backtrace_counter++)
		fprintf(stderr, "%s\n", backtrace_strings[backtrace_counter]);


	free(backtrace_strings);

#endif

	switch (signum) {
	case 0:
		return;
		break;
	case SIGSEGV:
		fprintf(stderr, "\n%s():  received SIGSEGV!\n", __FUNCTION__);
		break;
	case SIGFPE:
		fprintf(stderr, "\n%s():  received SIGFPE!\n", __FUNCTION__);
		break;
	default:
		fprintf(stderr, "\n%s():  received UNKNOWN SIGNAL %d!  ERROR! \n", __FUNCTION__, signum);
	}

	Terminate(EXIT_FAILURE, TRUE);

}

call_diff_setup (const char *prog, int argc, char * const *argv)
{
    int i;


    run_arg_free_p (call_diff_argc, call_diff_argv);
    call_diff_argc = 0;


    call_diff_add_arg (prog);
    for (i = 0; i < argc; i++)
	call_diff_add_arg (argv[i]);
}

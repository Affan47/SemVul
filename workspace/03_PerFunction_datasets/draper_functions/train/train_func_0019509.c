terminate_poll(int sig)

{

    if (sig != 0)
        report(stdout, GT_("terminated with signal %d\n"), sig);

#ifdef POP3_ENABLE


    if (!check_only)
	write_saved_lists(querylist, run.idfile);
#endif
}

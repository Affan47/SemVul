postwatch_proc (const char *repository, const char *filter, void *closure)
{
    char *cmdline;
    const char *srepos = Short_Repository (repository);

    TRACE (TRACE_FUNCTION, "postwatch_proc (%s, %s)", repository, filter);


    cmdline = format_cmdline (
#ifdef SUPPORT_OLD_INFO_FMT_STRINGS
	                      false, srepos,
#endif
	                      filter,
	                      "c", "s", cvs_cmd_name,
			      "I", "s", global_session_id,
#ifdef SERVER_SUPPORT
	                      "R", "s", referrer ? referrer->original : "NONE",
#endif
	                      "p", "s", srepos,
	                      "r", "s", current_parsed_root->directory,
	                      (char *) NULL);

    if (!cmdline || !strlen (cmdline))
    {
	if (cmdline) free (cmdline);
	error (0, 0, "postwatch proc resolved to the empty string!");
	return 1;
    }

    run_setup (cmdline);

    free (cmdline);


    return abs (run_exec (RUN_TTY, RUN_TTY, RUN_TTY,
			  RUN_NORMAL | RUN_SIGIGNORE));
}

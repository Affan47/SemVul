serve_global_option (char *arg)
{
# ifdef PROXY_SUPPORT


    if (reprocessing) return;
# endif

    if (arg[0] != '-' || arg[1] == '\0' || arg[2] != '\0')
    {
    error_return:
	if (alloc_pending (strlen (arg) + 80))
	    sprintf (pending_error_text,
		     "E Protocol error: bad global option %s",
		     arg);
	return;
    }
    switch (arg[1])
    {
	case 'l':
	    error(0, 0, "WARNING: global `-l' option ignored.");
	    break;
	case 'n':
	    noexec = 1;
	    logoff = 1;
	    break;
	case 'q':
	    quiet = 1;
	    break;
	case 'r':
	    cvswrite = 0;
	    break;
	case 'Q':
	    really_quiet = 1;
	    break;
	case 't':
	    trace++;
	    break;
	default:
	    goto error_return;
    }
}

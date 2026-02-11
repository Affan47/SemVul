mch_suspend()
{

#if defined(SIGTSTP) && !defined(__BEOS__)
    out_flush();
    settmode(TMODE_COOK);
    out_flush();

# if defined(FEAT_CLIPBOARD) && defined(FEAT_X11)
    loose_clipboard();
# endif

# if defined(_REENTRANT) && defined(SIGCONT)
    sigcont_received = FALSE;
# endif
    kill(0, SIGTSTP);
# if defined(_REENTRANT) && defined(SIGCONT)


    {
	long wait_time;
	for (wait_time = 0; !sigcont_received && wait_time <= 3L; wait_time++)

	    mch_delay(wait_time, FALSE);
    }
# endif

# ifdef FEAT_TITLE


    vim_free(oldtitle);
    oldtitle = NULL;
# endif
    settmode(TMODE_RAW);
    need_check_timestamps = TRUE;
    did_check_timestamps = FALSE;
#else
    suspend_shell();
#endif
}

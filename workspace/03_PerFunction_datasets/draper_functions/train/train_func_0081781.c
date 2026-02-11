deathtrap SIGDEFARG(sigarg)
{
    static int	entered = 0;


#ifdef SIGHASARG
    int		i;
#endif

#if defined(HAVE_SETJMP_H)


    if (lc_active)
    {
# if defined(SIGHASARG)
	lc_signal = sigarg;
# endif
	lc_active = FALSE;
	LONGJMP(lc_jump_env, 1);

    }
#endif

#ifdef SIGHASARG
# ifdef SIGQUIT


    if (in_mch_delay && sigarg == SIGQUIT)
	SIGRETURN;
# endif


    if (entered == 0
	    && (0
# ifdef SIGHUP
		|| sigarg == SIGHUP
# endif
# ifdef SIGQUIT
		|| sigarg == SIGQUIT
# endif
# ifdef SIGTERM
		|| sigarg == SIGTERM
# endif
# ifdef SIGPWR
		|| sigarg == SIGPWR
# endif
# ifdef SIGUSR1
		|| sigarg == SIGUSR1
# endif
# ifdef SIGUSR2
		|| sigarg == SIGUSR2
# endif
		)
	    && !vim_handle_signal(sigarg))
	SIGRETURN;
#endif


    ++entered;

#ifdef FEAT_EVAL

    set_vim_var_nr(VV_DYING, (long)entered);
#endif

#ifdef HAVE_STACK_LIMIT


    get_stack_limit();
#endif

#if 0


    {
# define VI_GDB_FILE "/tmp/vimgdb"
# define VIM_NAME "/usr/bin/vim"
	FILE *fp = fopen(VI_GDB_FILE, "w");
	if (fp)
	{
	    fprintf(fp,
		    "file %s\n"
		    "attach %d\n"
		    "set height 1000\n"
		    "bt full\n"
		    , VIM_NAME, getpid());
	    fclose(fp);
	    system("xterm -e gdb -x "VI_GDB_FILE);
	    unlink(VI_GDB_FILE);
	}
    }
#endif

#ifdef SIGHASARG

    for (i = 0; signal_info[i].sig != -1; i++)
	if (sigarg == signal_info[i].sig)
	    break;
    deadly_signal = sigarg;
#endif

    full_screen = FALSE;


    if (entered >= 3)
    {
	reset_signals();
	may_core_dump();
	if (entered >= 4)
	    _exit(8);
	exit(7);
    }
    if (entered == 2)
    {

	OUT_STR("Vim: Double signal, exiting\n");
	out_flush();
	getout(1);
    }


#ifdef SIGHASARG
    sprintf((char *)IObuff, "Vim: Caught deadly signal %s\n",
							 signal_info[i].name);
#else
    sprintf((char *)IObuff, "Vim: Caught deadly signal\n");
#endif


    preserve_exit();

#ifdef NBDEBUG
    reset_signals();
    may_core_dump();
    abort();
#endif

    SIGRETURN;
}

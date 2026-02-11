run_daemon(EpmdVars *g)
{
    register int child_pid, fd;

    dbg_tty_printf(g,2,"fork a daemon");


    if (( child_pid = fork()) < 0)
      {
#ifdef HAVE_SYSLOG_H
	syslog(LOG_ERR,"erlang mapper daemon cant fork %m");
#endif
	epmd_cleanup_exit(g,1);
      }
    else if (child_pid > 0)
      {
	dbg_tty_printf(g,2,"daemon child is %d",child_pid);
	epmd_cleanup_exit(g,0);
      }

    if (setsid() < 0)
      {
	dbg_perror(g,"epmd: Cant setsid()");
	epmd_cleanup_exit(g,1);
      }


    signal(SIGHUP, SIG_IGN);


    if ((child_pid = fork()) < 0)
      {
#ifdef HAVE_SYSLOG_H
	syslog(LOG_ERR,"erlang mapper daemon cant fork 2'nd time %m");
#endif
	epmd_cleanup_exit(g,1);
      }
    else if (child_pid > 0)
      {
	dbg_tty_printf(g,2,"daemon 2'nd child is %d",child_pid);
	epmd_cleanup_exit(g,0);
      }


    if (chdir("/") < 0)
      {
	dbg_perror(g,"epmd: chdir() failed");
	epmd_cleanup_exit(g,1);
      }

    umask(0);

    for (fd = 0; fd < g->max_conn ; fd++)
        close(fd);


    closelog();


    open("/dev/null", O_RDONLY);
    open("/dev/null", O_WRONLY);
    open("/dev/null", O_WRONLY);

    errno = 0;

    run(g);
}

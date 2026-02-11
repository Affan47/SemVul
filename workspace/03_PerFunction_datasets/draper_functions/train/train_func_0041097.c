os_printf(int prio, char *fmt, ... )
{
    va_list args;
    static char message[MAXSTRING + 1];

    message[MAXSTRING] = 0;
    va_start(args, fmt);
    vsnprintf(message, sizeof(message), fmt, args);
    va_end(args);

#ifdef HAVE_OS_SYSLOG
    if (get_dbg_dest() == DBG_SYS_LOG)
    {
	syslog(prio, "%s",message);
    }
    else
#endif
    {
	printf("%s %s\n", current_time(), message);
        fflush(stdout);
    }
}

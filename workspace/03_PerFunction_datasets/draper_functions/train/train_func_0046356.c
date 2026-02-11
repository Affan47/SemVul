initialize_userlist(void)
{
    struct utmp *ut;
    char *cp;

    times_on = 0;

    while(((ut = getutent()) != NULL) && (times_on < MAX_TTYS))
#ifdef	BSD
	{
#else
	if (ut->ut_type == USER_PROCESS) {
#endif
	    tty_list[times_on].username = malloc(ULIST_UNAME+1);
	    tty_list[times_on].tty = malloc(ULIST_TTY+1);
	    tty_list[times_on].locale = malloc(ULIST_LOCALE+1);
	    tty_list[times_on].line = malloc(ULIST_LINE+1);
	    memset (tty_list[times_on].username, 0, ULIST_UNAME+1);
	    memset (tty_list[times_on].tty, 0, ULIST_TTY+1);
	    memset (tty_list[times_on].locale, 0, ULIST_LOCALE+1);
	    memset (tty_list[times_on].line, 0, ULIST_LINE+1);

#ifdef	BSD
	    strncpy(tty_list[times_on].username, (char *) ut->ut_name, ULIST_UNAME);
#else
	    strncpy(tty_list[times_on].username, (char *) ut->ut_user, ULIST_UNAME);
	    cp = (char *) ut->ut_line;
	    if (!strncmp(cp, "tty", 3)) cp+=3;
	    strncpy(tty_list[times_on].tty, cp, ULIST_TTY);
#ifdef SUNOS
	    tty_list[times_on].ip_addr = 0;
#else
	    tty_list[times_on].ip_addr = ut->ut_addr;
#endif
#endif
	    cp = ut->ut_host;
	    if (*cp == ':')
		cp++;
	    strncpy(tty_list[times_on].locale, cp, ULIST_LOCALE);
	    if (strlen ((char *) ut->ut_host) > ULIST_LINE)
		if ((cp = strrchr(tty_list[times_on].locale, '.')) != NULL)
		    *cp = '\0';
	    strncpy(tty_list[times_on].line, (char *) ut->ut_line, ULIST_LINE);

	    tty_list[times_on].time = ut->ut_time;
	    times_on++;
	}
}

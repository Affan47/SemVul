utmpx_login(char *line, const char *user, const char *host)
{
    struct utmpx *ut, save_ut;
    pid_t   mypid = getpid();
    int     ret = (-1);


    while ((ut = getutxent())) {

	if (ut->ut_pid == mypid
	    && (   ut->ut_type == INIT_PROCESS
		|| ut->ut_type == LOGIN_PROCESS
		|| ut->ut_type == USER_PROCESS)) {
	    save_ut = *ut;
	    utmpx_update(&save_ut, line, user, host);
	    ret = 0;
	    break;
	}
    }
    if (ret == -1) {

        struct utmpx newut;
	memset(&newut, 0, sizeof(newut));
	newut.ut_pid = mypid;
        utmpx_update(&newut, line, user, host);
	ret = 0;
    }
    endutxent();
    return (ret);
}

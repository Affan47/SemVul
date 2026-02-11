_nc_home_terminfo(void)
{
    char *result = 0;
#if USE_HOME_TERMINFO
    char *home;

    if (use_terminfo_vars()) {
	if (MyBuffer == 0) {
	    if ((home = getenv("HOME")) != 0) {
		unsigned want = (strlen(home) + sizeof(PRIVATE_INFO));
		MyBuffer = typeMalloc(char, want);
		if (MyBuffer == 0)
		    _nc_err_abort(MSG_NO_MEMORY);
		(void) sprintf(MyBuffer, PRIVATE_INFO, home);
	    }
	}
	result = MyBuffer;
    }
#endif
    return result;
}

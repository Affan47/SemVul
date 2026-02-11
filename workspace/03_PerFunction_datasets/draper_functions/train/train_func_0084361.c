test_dashp( char *   value,
	    void *   ignored,
	    char **  errmsg )
{
    int  res = (atoi(value) <= 0);
    if (res)
	*errmsg = globus_libc_strdup("argument is not a positive integer");
    return res;
}

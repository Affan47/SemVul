setactive(struct protstream *conn, mystring_t *name)
{
    int result;
    char filename[1024];


    if (!strlen(string_DATAPTR(name))) {
	if (deleteactive(conn) != TIMSIEVE_OK)
	    return TIMSIEVE_FAIL;

	prot_printf(conn,"OK\r\n");
	return TIMSIEVE_OK;
    }

    result = scriptname_valid(name);
    if (result!=TIMSIEVE_OK)
    {
	prot_printf(conn,"NO \"Invalid script name\"\r\n");
	return result;
    }

    if (exists(string_DATAPTR(name))==FALSE)
    {
	prot_printf(conn,"NO (NONEXISTENT) \"Script does not exist\"\r\n");
	return TIMSIEVE_NOEXIST;
    }


    if (isactive(string_DATAPTR(name))==TRUE) {
	prot_printf(conn,"OK\r\n");
	return TIMSIEVE_OK;
    }


    snprintf(filename, sizeof(filename), "%s.bc", string_DATAPTR(name));


    result = symlink(filename, "defaultbc.NEW");
    if (result) {
	syslog(LOG_ERR, "symlink(%s, defaultbc.NEW): %m", filename);
	prot_printf(conn, "NO \"Can't make link\"\r\n");
	return TIMSIEVE_FAIL;
    }

    result = rename("defaultbc.NEW", "defaultbc");
    if (result) {
	unlink("defaultbc.NEW");
	syslog(LOG_ERR, "rename(defaultbc.NEW, defaultbc): %m");
	prot_printf(conn,"NO \"Error renaming\"\r\n");
	return TIMSIEVE_FAIL;
    }
    sync_log_sieve(sieved_userid);

    prot_printf(conn,"OK\r\n");
    return TIMSIEVE_OK;
}

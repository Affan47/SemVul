cli_versig(const char *md5, const char *dsig)
{
	mp_int n, e;
	char *pt, *pt2;


    if(strlen(md5) != 32 || !isalnum(md5[0])) {

	cli_errmsg("SECURITY WARNING: MD5 basic test failure.\n");
	return CL_EVERIFY;
    }

    mp_init(&n);
    mp_read_radix(&n, CLI_NSTR, 10);
    mp_init(&e);
    mp_read_radix(&e, CLI_ESTR, 10);

    if(!(pt = (char *) cli_decodesig(dsig, 16, e, n))) {
	mp_clear(&n);
	mp_clear(&e);
	return CL_EVERIFY;
    }

    pt2 = cli_str2hex(pt, 16);
    free(pt);

    cli_dbgmsg("cli_versig: Decoded signature: %s\n", pt2);

    if(strncmp(md5, pt2, 32)) {
	cli_dbgmsg("cli_versig: Signature doesn't match.\n");
	free(pt2);
	mp_clear(&n);
	mp_clear(&e);
	return CL_EVERIFY;
    }

    free(pt2);
    mp_clear(&n);
    mp_clear(&e);

    cli_dbgmsg("cli_versig: Digital signature is correct.\n");
    return CL_SUCCESS;
}

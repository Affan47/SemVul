warn_dlerror(const char *msg)
{
    const char *err = lt_dlerror();
    if (err)
	cli_warnmsg("%s: %s\n", msg, err);
    else
	cli_warnmsg("%s\n", err);
    return 0;
}

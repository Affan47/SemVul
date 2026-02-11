os_become_undo_atexit(void)
{
    trace(("os_become_undo_atexit()\n{\n"));
    assert(become_inited);
    if (become_active)
    {
	become_active = 0;
	if (!become_testing)
	{
#ifndef CONF_NO_seteuid
	    if (seteuid(0))
		nfatal("seteuid(0)");
	    if (setegid(0))
		nfatal("setegid(0)");
#if defined(DEBUG) && defined(__linux__)
	    if (!prctl(PR_GET_DUMPABLE, 0, 0, 0, 0))
	    {
		prctl(PR_SET_DUMPABLE, 1, 0, 0, 0);
	    }
#endif
#endif
	    become_active_uid = 0;
	    become_active_gid = 0;
	}
    }
    trace(("}\n"));
}

leave_suid(void)
{
    debug(21, 3) ("leave_suid: PID %d called\n", (int) getpid());
    if (Config.effectiveGroup) {
#if HAVE_SETGROUPS
	setgroups(1, &Config2.effectiveGroupID);
#endif
	if (setgid(Config2.effectiveGroupID) < 0)
	    debug(50, 0) ("ALERT: setgid: %s\n", xstrerror());
    }
    if (geteuid() != 0)
	return;

    if (Config.effectiveUser == NULL)
	return;
    debug(21, 3) ("leave_suid: PID %d giving up root, becoming '%s'\n",
	(int) getpid(), Config.effectiveUser);
    if (!Config.effectiveGroup) {
	if (setgid(Config2.effectiveGroupID) < 0)
	    debug(50, 0) ("ALERT: setgid: %s\n", xstrerror());
	if (initgroups(Config.effectiveUser, Config2.effectiveGroupID) < 0) {
	    debug(50, 0) ("ALERT: initgroups: unable to set groups for User %s "
		"and Group %u", Config.effectiveUser,
		(unsigned) Config2.effectiveGroupID);
	}
    }
#if HAVE_SETRESUID
    if (setresuid(Config2.effectiveUserID, Config2.effectiveUserID, 0) < 0)
	debug(50, 0) ("ALERT: setresuid: %s\n", xstrerror());
#elif HAVE_SETEUID
    if (seteuid(Config2.effectiveUserID) < 0)
	debug(50, 0) ("ALERT: seteuid: %s\n", xstrerror());
#else
    if (setuid(Config2.effectiveUserID) < 0)
	debug(50, 0) ("ALERT: setuid: %s\n", xstrerror());
#endif
    restoreCapabilities(1);

    enableCoredumps();
}

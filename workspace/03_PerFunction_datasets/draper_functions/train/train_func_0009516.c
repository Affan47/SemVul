find_unused_loop_device (void) {
	struct looplist ll;
	char *devname = NULL;
	int fd;

	if (looplist_open(&ll, LLFLG_FREEONLY) == -1) {
		error(_("%s: /dev directory does not exist."), progname);
		return NULL;
	}

	if ((fd = looplist_next(&ll)) != -1) {
		close(fd);
		devname = xstrdup(ll.name);
	}
	looplist_close(&ll);
	if (devname)
		return devname;

	if (!ll.ct_succ && ll.ct_perm)
		error(_("%s: no permission to look at /dev/loop%s<N>"), progname,
				(ll.flag & LLFLG_SUBDIR) ? "/" : "");
	else if (ll.ct_succ)
		error(_("%s: could not find any free loop device"), progname);
	else
		error(_(
		    "%s: Could not find any loop device. Maybe this kernel "
		    "does not know\n"
		    "       about the loop device? (If so, recompile or "
		    "`modprobe loop'.)"), progname);
	return NULL;
}

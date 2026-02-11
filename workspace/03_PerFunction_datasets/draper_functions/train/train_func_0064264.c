maybe_link(void)
{
	if (nlink >= 2) {
		char *old = find_link(major, minor, ino, mode, collected);
		if (old)
			return (sys_link(old, collected) < 0) ? -1 : 1;
	}
	return 0;
}

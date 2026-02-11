cpio_mknod(const char *name, unsigned int mode,
		       uid_t uid, gid_t gid, char dev_type,
		       unsigned int maj, unsigned int min)
{
	char s[256];
	time_t mtime = time(NULL);

	if (dev_type == 'b')
		mode |= S_IFBLK;
	else
		mode |= S_IFCHR;

	sprintf(s,"%s%08X%08X%08lX%08lX%08X%08lX"
	       "%08X%08X%08X%08X%08X%08X%08X",
		"070701",
		ino++,
		mode,
		(long) uid,
		(long) gid,
		1,
		(long) mtime,
		0,
		3,
		1,
		maj,
		min,
		(unsigned)strlen(name) + 1,
		0);
	push_hdr(s);
	push_rest(name);
	return 0;
}

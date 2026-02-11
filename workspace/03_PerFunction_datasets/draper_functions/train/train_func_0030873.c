ibox_acl_check_dir(const char *dirname, const char *subject, int flags)
{
	int myflags;

	if(!do_ibox_acl_get(dirname, subject, &myflags)) {
		errno = EACCES;
		return 0;
	}

	if((flags & myflags) == flags) {
		return 1;
	} else {
		errno = EACCES;
		return 0;
	}
}

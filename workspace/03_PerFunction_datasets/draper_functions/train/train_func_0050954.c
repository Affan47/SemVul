__lxstat(int ver, const char *filename, struct stat *buf)
{
    int apt = 0;
    int e;
    funcptr __stat;

    auto_apt_setup();
 again:
    DPRINT(("lstat: filename=%s \n", filename));
    if (!apt && detectdb_file) detect_package(filename, __FUNCTION__);
    __stat = load_library_symbol("__lxstat");
    if (__stat == NULL) {
	errno = ENOENT;
	return -1;
    }
    DPRINT(("lstat = %p\n", __stat));
    e = __stat(ver, filename, buf);
    DPRINT(("lstat: filename=%s e=%d\n", filename, e));
    if (apt_hook[APT_HOOK_STAT] && e < 0) {
	switch (errno) {
	case ENOENT:
	    if (*filename == '/') {
		if (!apt && apt_get_install_for_file(filename)) {
		    apt = 1;
		    goto again;
		}
	    }
	    break;
	default:
	    break;
	}
    }
    return e;
}

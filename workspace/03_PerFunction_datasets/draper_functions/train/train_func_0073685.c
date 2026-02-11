chroot(const char *path) {
	int result;
	char canonic[MAXPATHLEN];

	REFCOUNT;

	if (!libc_handle)
		initialize();

#if DEBUG
	debug(2,"chroot(%s)\n",path);
#endif

	canonicalize(path, canonic);
	result = true_chroot(path);


	logg("%d\tchroot\t%s\t#%s\n", result, canonic, error(result));
	return result;
}

fchmod(int filedes, mode_t mode) {
	int result;

	REFCOUNT;

	if (!libc_handle)
		initialize();

#if DEBUG
	debug(2,"fchmod\n");
#endif

	result = true_fchmod(filedes, mode);
	logg("%d\tfchmod\t%d\t0%04o\t#%s\n",result,filedes,mode,error(result));
	return result;
}

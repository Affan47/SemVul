insert_floppy()
{
	remove_floppy();

	char *path = bx_options.floppy.path;

	if (strlen(path) == 0)
		return false;

	int status = open(path, O_RDWR
#ifdef HAVE_O_FSYNC
			| O_FSYNC
#else
# ifdef O_SYNC
			| O_SYNC
# endif
#endif
#ifdef O_BINARY
			| O_BINARY
#endif
			);
	bool rw = true;
	if (status < 0) {
		status = open(path, O_RDONLY
#ifdef O_BINARY
					| O_BINARY
#endif
					);
		rw = false;
	}
	if (status < 0) {
		D(bug("Inserting of floppy failed."));
		return false;
	}

	D(bug("Floppy inserted %s", rw ? "read-write" : "read-only"));
	drive_fd = status;

	set_floppy_geometry();

	floppy_changed = true;
	panic_floppy_error = 0;
	return true;
}

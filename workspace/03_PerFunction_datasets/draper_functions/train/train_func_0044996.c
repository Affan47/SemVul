fd_flags_teardown(void *p)
{
    int retval;
    struct fd_struct **f = (struct fd_struct **)p;

    retval = unlink(f[0]->filename);
    if (f[0]->unlinked) {
        if ((retval >= 0) || (errno != ENOENT)) {
            perror("duplicate unlink");
	    retval = -1;
        } else {
	    retval = 0;
	}
    } else if (retval < 0) {
        perror("unlink");
    }

    free(p);

    return retval;
}

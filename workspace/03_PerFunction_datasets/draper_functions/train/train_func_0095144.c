open_fd_struct(char *filename, int flags, int do_unlink)
{
    struct fd_struct *f;
    int retval;

    f = malloc(sizeof(*f));
    if (f==NULL) {
        perror("malloc");
        goto out;
    }
    memset(f, 0, sizeof(*f));

    strncpy(f->filename, filename, MAX_TEST_FILENAME);
    f->filename[MAX_TEST_FILENAME] = '\0';

    if ((flags & (O_CREAT | O_EXCL)) == (O_CREAT | O_EXCL)) {
	(void)unlink(f->filename);
    }

    f->fd = open(f->filename, flags, TEST_FILE_MODE);
    if (f->fd < 0) {
        perror("open");
	retval = f->fd;
	goto out_free;
    }

    retval = update_fd_struct(f);
    if (retval < 0) {
        goto out_free;
    }

    f->unlinked = do_unlink;
    if (do_unlink) {
        retval = unlink(filename);
        if (retval < 0) {
	    perror("unlink");
            goto out_free;
        }
    }

out:
    return f;

out_free:
    free(f);
    return NULL;
}

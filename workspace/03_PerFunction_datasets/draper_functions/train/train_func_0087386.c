apprentice_compile(struct magic_set *ms, struct magic **magicp,
    uint32_t *nmagicp, const char *fn)
{
	int fd;
	char *dbname;
	int rv = -1;

	dbname = mkdbname(ms, fn, 1);

	if (dbname == NULL)
		goto out;

	if ((fd = open(dbname, O_WRONLY|O_CREAT|O_TRUNC|O_BINARY, 0644)) == -1) {
		file_error(ms, errno, "cannot open `%s'", dbname);
		goto out;
	}

	if (write(fd, ar, sizeof(ar)) != (ssize_t)sizeof(ar)) {
		file_error(ms, errno, "error writing `%s'", dbname);
		goto out;
	}

	if (lseek(fd, (off_t)sizeof(struct magic), SEEK_SET)
	    != sizeof(struct magic)) {
		file_error(ms, errno, "error seeking `%s'", dbname);
		goto out;
	}

	if (write(fd, *magicp, (sizeof(struct magic) * *nmagicp))
	    != (ssize_t)(sizeof(struct magic) * *nmagicp)) {
		file_error(ms, errno, "error writing `%s'", dbname);
		goto out;
	}

	(void)close(fd);
	rv = 0;
out:
	free(dbname);
	return rv;
}

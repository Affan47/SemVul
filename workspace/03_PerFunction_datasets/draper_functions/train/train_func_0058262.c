readdir(DIR *dir)
{
	struct dirent *dent;
	int rv;

	if (!dir->bytes_left) {
		rv = getdents(dir->__fd, dir->buffer, sizeof(dir->buffer));
		if (rv <= 0)
			return NULL;
		dir->bytes_left = rv;
		dir->next = dir->buffer;
	}

	dent = dir->next;
	dir->next = (struct dirent *)((char *)dir->next + dent->d_reclen);
	dir->bytes_left -= dent->d_reclen;

	return dent;
}

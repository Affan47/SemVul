write_object_files(object_data *d)
{
	int fd;

	if (p_mkdir(d->dir, GIT_OBJECT_DIR_MODE) < 0)
		cl_assert(errno == EEXIST);

	cl_assert((fd = p_creat(d->file, S_IREAD | S_IWRITE)) >= 0);
	cl_must_pass(p_write(fd, d->bytes, d->blen));

	p_close(fd);
}

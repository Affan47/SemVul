x_size(void*priv,uint64_t *size) {
	struct privstr *ps = priv;
	int fd = ps->fd;
	off_t res;

	gp_log (GP_LOG_DEBUG, "x_size","(%p,%u)", priv, (unsigned int)*size);
	res = lseek (fd, 0, SEEK_END);
	if (res == -1) {
		perror ("x_size: lseek SEEK_END");
		return GP_ERROR_IO;
	}
	res = lseek (fd, 0, SEEK_CUR);
	if (res == -1) {
		perror ("x_size: lseek SEEK_CUR");
		return GP_ERROR_IO;
	}
	*size = res;
	res = lseek (fd, 0, SEEK_SET);
	if (res == -1) {
		perror ("x_size: lseek SEEK_SET");
		return GP_ERROR_IO;
	}
	return GP_OK;
}

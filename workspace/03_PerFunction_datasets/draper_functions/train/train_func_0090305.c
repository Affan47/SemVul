open_ctrl(char *device_path)
{
	int fd;
	struct stat stat_buf;
	array_data_t *array_data;

	if ((fd = open(device_path, O_RDONLY)) < 0)
		perror("open");
	fstat(fd, &stat_buf);
	if (!(S_ISBLK(stat_buf.st_mode) || (S_ISCHR(stat_buf.st_mode)))) {
		printf("%s is not a valid block or char device...\n",
		       device_path);
		return NULL;
	}

	if (!(array_data = xmalloc(sizeof (*array_data))))
		return NULL;
	array_data->fd = fd;
	array_data->device_major.type =
	    S_ISBLK(stat_buf.st_mode) ? BLOCK_DEVICE : CHAR_DEVICE;
	array_data->device_major.major = major(stat_buf.st_rdev);
	array_data->device_major.minor = minor(stat_buf.st_rdev);

	return array_data;
}

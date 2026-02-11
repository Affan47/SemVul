bs_aio_open(struct scsi_lu *lu, char *path, int *fd, uint64_t *size)
{
	*fd = backed_file_open(path, O_RDWR|O_LARGEFILE|O_DIRECT, size);

	if (*fd == -1 && (errno == EACCES || errno == EROFS)) {
		*fd = backed_file_open(path, O_RDONLY|O_LARGEFILE|O_DIRECT,
				       size);
		lu->attrs.readonly = 1;
	}
	if (*fd < 0)
		return *fd;
	return 0;
}

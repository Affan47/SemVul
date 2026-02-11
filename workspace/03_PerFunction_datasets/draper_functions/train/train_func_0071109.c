bs_rdwr_open(struct scsi_lu *lu, char *path, int *fd, uint64_t *size)
{
	*fd = backed_file_open(path, O_RDWR|O_LARGEFILE|lu->bsoflags, size);

	if (*fd == -1 && errno == EACCES) {
		*fd = backed_file_open(path, O_RDONLY|O_LARGEFILE|lu->bsoflags,
				       size);
		lu->attrs.readonly = 1;
	}
	if (*fd < 0)
		return *fd;

	return 0;
}

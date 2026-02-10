gzip_load_kernel(CHAR16 *kname, kdesc_t *kd)
{
	EFI_STATUS status;
	INT32 ret;
	fops_fd_t fd;

	status = fops_open(kname, &fd);
	if (EFI_ERROR(status)) return ELILO_LOAD_ERROR;

	ret = gunzip_kernel(fd, kd);

	fops_close(fd);

	return ret;
}

fops_infosize(fops_fd_t fd, UINT64 *size)
{
	fdesc_t *f;

	if (FDESC_INVALID_FD(fd) || size == NULL) return EFI_INVALID_PARAMETER;

	f = FDESC_F(fd);

	return f->fops->infosize(f->fops->intf, f->fh, size);
}

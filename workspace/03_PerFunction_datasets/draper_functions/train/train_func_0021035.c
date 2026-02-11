plain_probe(CHAR16 *kname)
{
	Elf64_Ehdr ehdr;
	EFI_STATUS status;
	INTN ret = -1;
	fops_fd_t fd;
	UINTN size = sizeof(ehdr);

	status = fops_open(kname, &fd);
	if (EFI_ERROR(status))
		return -1;

	VERB_PRT(3, {
		Print(L"plain_probe: kname=%s\n", kname);
	});
	status = fops_read(fd, &ehdr, &size);
	if (EFI_ERROR(status) || size != sizeof(ehdr))
		goto error;

	ret = is_valid_header(&ehdr);
error:
	fops_close(fd);
	return ret;
}

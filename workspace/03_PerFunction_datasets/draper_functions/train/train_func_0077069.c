close_devices(VOID)
{
	INTN i;

	for(i=0; i < FILEOPS_FD_MAX; i++) {
		fops_close(i);
	}
	free(dev_tab);


	uninstall_filesystems();

	return 0;
}

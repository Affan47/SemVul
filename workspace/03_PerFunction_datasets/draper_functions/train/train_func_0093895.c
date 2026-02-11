exfat_close(struct exfat_dev* dev)
{
#ifdef USE_UBLIO
	if (ublio_close(dev->ufh) != 0)
		exfat_error("failed to close ublio");
#endif
	if (close(dev->fd) != 0)
	{
		free(dev);
		exfat_error("failed to close device");
		return 1;
	}
	free(dev);
	return 0;
}

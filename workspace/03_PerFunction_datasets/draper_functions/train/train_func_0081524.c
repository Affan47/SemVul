musb_get_device_status(mud_device *pd, unsigned int *status)
{
	int i, fd=FD_NA;
	enum HPMUD_RESULT stat = HPMUD_R_DEVICE_BUSY;
	int r=1;

	pthread_mutex_lock(&pd->mutex);

	if (pd->io_mode == HPMUD_DOT4_BRIDGE_MODE || pd->io_mode == HPMUD_UNI_MODE)
		*status = NFAULT_BIT;
	else
	{

		for (i=1; i<MAX_FD; i++)
		{
			if (fd_table[i].hd != NULL)
			{
				fd = i;
				break;
			}
		}

		if (fd == FD_NA)
		{

			if ((fd = claim_id_interface(libusb_dev)) != MAX_FD)
			{
				r = device_status(fd, status);
				release_interface(&fd_table[fd]);
			}
		}
		else
		{

			r = device_status(fd, status);
		}
	}

	pthread_mutex_unlock(&pd->mutex);

	if (r != 0)
		goto bugout;

	stat = HPMUD_R_OK;

bugout:
	return stat;
}

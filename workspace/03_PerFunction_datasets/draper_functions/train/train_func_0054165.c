flex_download(int device, int file)
{
	int byte, bit;
	unsigned char data;

	if (debug)
		printf("Downloading code\n");

	for(byte = 0 ; ; byte++)
	{
		if (debug)
			printf("Downloading byte %i\n", byte);

		if (read(file, &data, 1) != 1)
		{
			if (!quiet)
				fprintf(stderr, "Unexpected end of file\n");
			return -1;
		}

		for (bit = 0 ; bit < 8 ; bit++)
		{
			set_DATA0(device, data & 0x01);
			set_DCLK(device, 1);
			set_DCLK(device, 0);
			data >>= 1;

			if (get_nSTATUS(device) == 0)
			{
				if (!quiet)
					fprintf(stderr, "Checksum error\n");
				return -1;
			}

			if (get_CONF_DONE(device) == 1)
			{
				if (!quiet)
					printf("%i bytes downloaded\n", byte);
				return 0;
			}
		}
	}
}

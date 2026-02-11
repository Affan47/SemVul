cmd_radiotest(int transport, int argc, char *argv[])
{
	uint8_t array[8];
	uint16_t freq, level, test;

	OPT_HELP(3, NULL);

	freq = atoi(argv[0]);

	if (!strncasecmp(argv[1], "0x", 2))
		level = strtol(argv[1], NULL, 16);
	else
		level = atoi(argv[1]);

	test = atoi(argv[2]);

	memset(array, 0, sizeof(array));
	array[0] = test & 0xff;
	array[1] = test >> 8;
	array[2] = freq & 0xff;
	array[3] = freq >> 8;
	array[4] = level & 0xff;
	array[5] = level >> 8;

	return transport_write(transport, CSR_VARID_RADIOTEST, array, 8);
}

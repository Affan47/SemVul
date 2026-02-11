cmd_faultarg(int transport, int argc, char *argv[])
{
	uint8_t array[8];
	uint16_t error;
	int err;

	OPT_HELP(0, NULL);

	memset(array, 0, sizeof(array));

	err = transport_read(transport, CSR_VARID_FAULT_ARG, array, 8);
	if (err < 0)
		return -1;

	error = array[0] | (array[1] << 8);

	printf("Fault code: 0x%02x (%s)\n", error,
					error < 0x100 ? "valid" : "invalid");

	return 0;
}

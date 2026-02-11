cmd_pscheck(int transport, int argc, char *argv[])
{
	uint8_t array[256];
	uint16_t pskey, size;
	int i;

	OPT_HELP(1, NULL);

	psr_read(argv[0]);

	while (psr_get(&pskey, array, &size) == 0) {
		printf("0x%04x =", pskey);
		for (i = 0; i < size; i++)
			printf(" 0x%02x", array[i]);
		printf("\n");
	}

	return 0;
}

print_options(unsigned int optsnr, uint16_t *optsp)
{
	unsigned int i;

	printf(" ");
	for(i = 0; i < optsnr; i++) {
		printf("%d", (optsp[i] & 0xFF00) >> 8);

		if ((optsp[i] & 0x00FF) != 0x00FF)
			printf(":%d", (optsp[i] & 0x00FF));

		printf("%c", (i != optsnr - 1) ? ',' : ' ');
	}
}

dump_bram(struct fpga_config* cfg)
{
	int row, i, j, off, newline;

	newline = 0;
	for (row = 0; row < 4; row++) {
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 18*130; j++) {
				if (cfg->bits.d[BRAM_DATA_START + row*144*130
					  + i*18*130 + j])
					break;
			}
			if (j >= 18*130)
				continue;
			if (!newline) {
				newline = 1;
				printf("\n");
			}
			printf("br%i ramb16 i%i\n", row, i);
			printf("{\n");
			off = BRAM_DATA_START + row*144*130 + i*18*130;
			printf_ramb16_data(cfg->bits.d, off);
			printf("}\n");
		}
	}
	return 0;
}

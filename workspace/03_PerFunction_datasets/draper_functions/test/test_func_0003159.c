printf_lut(const uint8_t* bits, int row, int major,
	int minor, int v32_i)
{
	char bit_str[64];
	uint64_t u64;
	int i, num_bits_on;

	u64 = frame_get_lut64(&bits[minor*FRAME_SIZE], v32_i);
	if (u64) {
		num_bits_on = 0;
		for (i = 0; i < 64; i++) {
			if (u64 & (1ULL << i))
				num_bits_on++;
		}
		if (num_bits_on < 5) {
			printf("r%i ma%02i v32_%02i mip%02i_lut", row,
				major, v32_i, minor);
			for (i = 0; i < 64; i++) {
				if (u64 & (1ULL << i))
					printf(" b%i", i);
			}
			printf("\n");
		} else {
			for (i = 0; i < 64; i++)
				bit_str[i] = (u64 & (1ULL << i)) ? '1' : '0';
			printf("r%i ma%02i v32_%02i mip%02i_lut %.64s\n", row,
				major, v32_i, minor, bit_str);
		}
	}
}

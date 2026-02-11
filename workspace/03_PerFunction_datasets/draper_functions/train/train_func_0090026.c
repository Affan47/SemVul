pgm_dw2_decrypt(void)
{

	int i;
	data16_t *src = (data16_t *) (memory_region(REGION_CPU1)+0x100000);

	int rom_size = 0x80000;

	for(i=0; i<rom_size/2; i++) {
		data16_t x = src[i];

		if(((i & 0x020890) == 0x000000)
		   || ((i & 0x020000) == 0x020000 && (i & 0x001500) != 0x001400))
			x ^= 0x0002;

		if(((i & 0x020400) == 0x000000 && (i & 0x002010) != 0x002010)
		   || ((i & 0x020000) == 0x020000 && (i & 0x000148) != 0x000140))
			x ^= 0x0400;

		src[i] = x;
	}
}

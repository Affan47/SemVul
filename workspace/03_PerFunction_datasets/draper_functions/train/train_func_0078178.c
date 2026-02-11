guid_gen_syndrome_table(void)
{
	unsigned i;
	unsigned j;


	for (i = 0; i < 256; i++) {
		unsigned syn = i;
		for (j = 0; j < 8; j++) {

			syn <<= 1;
			if (syn & 0x80)
				syn ^= HEC_GENERATOR;
		}
		syndrome_table[i] = (uint8) syn;
	}
}

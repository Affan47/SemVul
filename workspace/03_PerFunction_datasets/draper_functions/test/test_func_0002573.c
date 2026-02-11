generate_tables_ascii(pkzip_cmp_s *mpq_pkzip) {


	const uint16_t *code_asc = &pkzip_code_asc[0xFF];
	uint32_t acc;
	uint32_t add;
	uint16_t count;


	for (count = 0x00FF; code_asc >= pkzip_code_asc; code_asc--, count--) {
		uint8_t *bits_asc = mpq_pkzip->bits_asc + count;
		uint8_t bits_tmp  = *bits_asc;


		if (bits_tmp <= 8) {
			add = (1 << bits_tmp);
			acc = *code_asc;
			do {
				mpq_pkzip->offs_2c34[acc]  = (uint8_t)count;
				acc                       += add;
			} while (acc < 0x100);
		} else {
			if ((acc = (*code_asc & 0xFF)) != 0) {
				mpq_pkzip->offs_2c34[acc] = 0xFF;
				if (*code_asc & 0x3F) {


					bits_tmp  -= 4;
					*bits_asc  = bits_tmp;
					add        = (1 << bits_tmp);
					acc        = *code_asc >> 4;
					do {
						mpq_pkzip->offs_2d34[acc]  = (uint8_t)count;
						acc                       += add;
					} while (acc < 0x100);
				} else {


					bits_tmp  -= 6;
					*bits_asc  = bits_tmp;
					add        = (1 << bits_tmp);
					acc        = *code_asc >> 6;
					do {
						mpq_pkzip->offs_2e34[acc]  = (uint8_t)count;
						acc                       += add;
					} while (acc < 0x80);
				}
			} else {


				bits_tmp  -= 8;
				*bits_asc  = bits_tmp;
				add        = (1 << bits_tmp);
				acc        = *code_asc >> 8;
				do {
					mpq_pkzip->offs_2eb4[acc]  = (uint8_t)count;
					acc                       += add;
				} while (acc < 0x100);
			}
		}
	}
}

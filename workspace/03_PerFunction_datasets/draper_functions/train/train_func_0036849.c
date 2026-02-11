rlp_crc24polinomial_calculate(u8 *data, int length, u32 *polinomial)
{

	int i;
	u8 cur;

	*polinomial = 0x00ffffff;

	for (i = 0; i < length; i++) {
		cur = (*polinomial & 0x0000ffff) ^ data[i];
		*polinomial = (*polinomial >> 8) ^ CRC24_Table[cur];
	}

	*polinomial = ((~*polinomial) & 0x00ffffff);
}

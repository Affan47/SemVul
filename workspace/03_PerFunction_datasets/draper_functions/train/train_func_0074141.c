tsys01_crc_valid(u16 *n_prom)
{
	u8 cnt;
	u8 sum = 0;

	for (cnt = 0; cnt < TSYS01_PROM_WORDS_NB; cnt++)
		sum += ((n_prom[0] >> 8) + (n_prom[0] & 0xFF));

	return (sum == 0);
}

rdb_crc (uae_u8 *p)
{
	uae_u32 sum;
	int i, blocksize;

	sum =0;
	blocksize = rl (p + 1 * 4);
	for (i = 0; i < blocksize; i++)
		sum += rl (p + i * 4);
	sum = -sum;
	pl (p, 2, sum);
}

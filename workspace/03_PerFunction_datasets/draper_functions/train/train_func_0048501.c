shl_block(block_t res, const block_t x)
{
	int i;
	for (i = 0; i < 15; i++) {
		res[i] = (x[i] << 1) | (x[i+1] >> 7);
	}
	res[15] = x[15] << 1;
}

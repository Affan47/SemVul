gf128_mul2(block_t res, const block_t x)
{
	int msb = x[0] & 0x80;
	shl_block(res, x);
	if (msb) {
		res[15] ^= 0x87;
	}
}

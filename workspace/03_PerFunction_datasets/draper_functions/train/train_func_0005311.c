chacha20_docrypt(u32 *state, u8 *dst, const u8 *src,
			     unsigned int bytes)
{
	u8 stream[CHACHA20_BLOCK_SIZE];

	if (dst != src)
		memcpy(dst, src, bytes);

	while (bytes >= CHACHA20_BLOCK_SIZE) {
		chacha20_block(state, stream);
		crypto_xor(dst, stream, CHACHA20_BLOCK_SIZE);
		bytes -= CHACHA20_BLOCK_SIZE;
		dst += CHACHA20_BLOCK_SIZE;
	}
	if (bytes) {
		chacha20_block(state, stream);
		crypto_xor(dst, stream, bytes);
	}
}

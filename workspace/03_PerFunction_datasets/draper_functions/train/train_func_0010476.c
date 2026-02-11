TestBitBufferWriteRandom(CuTest* tc)
{
	int32_t noise_length = 100;
	uint8_t bits[noise_length];

	struct BitBuffer* buf = bitbuf_new(8);
	srand(15);

	for (int32_t i=0;i<noise_length;i++) {
		uint8_t bit = rand() % 2;

		bits[i] = bit;
		bitbuf_put_bit(buf, bit);
	}

	for (int32_t i=0;i<noise_length;i++) {
		CuAssertIntEquals(tc, bits[i], 0 < (buf->data[i/8] & (1 << (7 - i % 8))));
	}

	bitbuf_del(buf);
}

PBKDF2_SHA256_80_128_8way(const uint32_t *tstate,
	const uint32_t *ostate, const uint32_t *salt, uint32_t *output)
{
	uint32_t istate[8 * 8] __attribute__((aligned(32)));
	uint32_t ostate2[8 * 8] __attribute__((aligned(32)));
	uint32_t ibuf[8 * 16] __attribute__((aligned(32)));
	uint32_t obuf[8 * 16] __attribute__((aligned(32)));
	int i, j;

	memcpy(istate, tstate, 8 * 32);
	sha256_transform_8way(istate, salt, 0);

	memcpy(ibuf, salt + 8 * 16, 8 * 16);
	for (i = 0; i < 8; i++)
		ibuf[8 * 5 + i] = 0x80000000;
	memset(ibuf + 8 * 6, 0x00, 8 * 36);
	for (i = 0; i < 8; i++)
		ibuf[8 * 15 + i] = 0x000004a0;

	for (i = 0; i < 8; i++)
		obuf[8 * 8 + i] = 0x80000000;
	memset(obuf + 8 * 9, 0x00, 8 * 24);
	for (i = 0; i < 8; i++)
		obuf[8 * 15 + i] = 0x00000300;

	for (i = 0; i < 4; i++) {
		memcpy(obuf, istate, 8 * 32);
		ibuf[8 * 4 + 0] = i + 1;
		ibuf[8 * 4 + 1] = i + 1;
		ibuf[8 * 4 + 2] = i + 1;
		ibuf[8 * 4 + 3] = i + 1;
		ibuf[8 * 4 + 4] = i + 1;
		ibuf[8 * 4 + 5] = i + 1;
		ibuf[8 * 4 + 6] = i + 1;
		ibuf[8 * 4 + 7] = i + 1;
		sha256_transform_8way(obuf, ibuf, 0);

		memcpy(ostate2, ostate, 8 * 32);
		sha256_transform_8way(ostate2, obuf, 0);
		for (j = 0; j < 8 * 8; j++)
			output[8 * 8 * i + j] = swab32(ostate2[j]);
	}
}

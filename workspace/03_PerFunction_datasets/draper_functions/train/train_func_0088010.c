SHA512_Core_Init(SHA512_State *s) {
    static const uint64 iv[] = {
	INIT(0x6a09e667, 0xf3bcc908),
	INIT(0xbb67ae85, 0x84caa73b),
	INIT(0x3c6ef372, 0xfe94f82b),
	INIT(0xa54ff53a, 0x5f1d36f1),
	INIT(0x510e527f, 0xade682d1),
	INIT(0x9b05688c, 0x2b3e6c1f),
	INIT(0x1f83d9ab, 0xfb41bd6b),
	INIT(0x5be0cd19, 0x137e2179),
    };
    int i;
    for (i = 0; i < 8; i++)
	s->h[i] = iv[i];
}

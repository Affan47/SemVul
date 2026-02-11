morus_initialization(const uint8_t *key, const uint8_t *iv, __m128i (*state)[2])
{
        int i;
	__m128i  tmp[2];
	tmp[0] = SETZERO();
	tmp[1] = SETZERO();

	state[0][0] = _mm_load_si128((__m128i*)iv); state[0][1] = SETZERO();
	state[1][0] = _mm_load_si128((__m128i*)key); state[1][1] = _mm_load_si128((__m128i*)key);
	state[2][0] = SETONE(); state[2][1] = SETONE();
	state[3][0] = SETZERO(); state[3][1] = SETZERO();
	state[4][0] = _mm_set_epi8(0x62,0x79,0xe9,0x90,0x59,0x37,0x22,0x15,0x0d,0x08,0x05,0x03,0x02,0x01,0x1, 0x0);
	state[4][1] = _mm_set_epi8(0xdd,0x28,0xb5,0x73,0x42,0x31,0x11,0x20,0xf1,0x2f,0xc2,0x6d,0x55,0x18,0x3d,0xdb);

        for (i = 0; i < 16; i++) morus_stateupdate(tmp, state);

        state[1][0] = XOR(state[1][0], _mm_load_si128((__m128i*)key));
	state[1][1] = XOR(state[1][1], _mm_load_si128((__m128i*)key));
}

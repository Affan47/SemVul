morus_initialization(const uint8_t *key, const uint8_t *iv, uint64_t state[][4])
{
        int i;
        uint64_t temp[4]  = {0,0,0,0};
        uint8_t con[32] = {0x0,0x1,0x01,0x02,0x03,0x05,0x08,0x0d,0x15,0x22,0x37,0x59,0x90,0xe9,0x79,0x62, 0xdb, 0x3d, 0x18, 0x55, 0x6d, 0xc2, 0x2f, 0xf1, 0x20, 0x11, 0x31, 0x42, 0x73, 0xb5, 0x28, 0xdd};
		uint64_t ekey[4];

		memcpy(ekey, key, 16);
		ekey[3] = ekey[1]; ekey[2] = ekey[0];
		memcpy(state[0], iv, 16);   memset(state[0]+2, 0, 16);
        memcpy(state[1], ekey, 32);
		memset(state[2], 0xff, 32);
        memset(state[3], 0, 32);
        memcpy(state[4], con, 32);

        for (i = 0; i < 4;  i++) temp[i] = 0;
        for (i = 0; i < 16; i++) morus_stateupdate(temp, state);
        for (i = 0; i < 4;  i++) state[1][i] ^= ((uint64_t*)ekey)[i];
}

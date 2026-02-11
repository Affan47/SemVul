mix_columns_inv(uint8_t *state)
{
	int i;
	uint8_t cpy[4];

	for (i = 0; i < 4; i++) {
		cpy[0] = state[0 * 4 + i];
		cpy[1] = state[1 * 4 + i];
		cpy[2] = state[2 * 4 + i];
		cpy[3] = state[3 * 4 + i];
		state[i] = gm14(cpy[0]) ^ gm9(cpy[3]) ^ gm13(cpy[2]) ^ gm11(cpy[1]);
		state[4+i] = gm14(cpy[1]) ^ gm9(cpy[0]) ^ gm13(cpy[3]) ^ gm11(cpy[2]);
		state[8+i] = gm14(cpy[2]) ^ gm9(cpy[1]) ^ gm13(cpy[0]) ^ gm11(cpy[3]);
		state[12+i] = gm14(cpy[3]) ^ gm9(cpy[2]) ^ gm13(cpy[1]) ^ gm11(cpy[0]);
	}
}

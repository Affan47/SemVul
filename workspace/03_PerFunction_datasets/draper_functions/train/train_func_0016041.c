chacha_gen(const u8 *key, const u64 block_counter, const u64 public_msg_num, u32 x[16]) {
	x[0] = CHACHA_CONST[0];
	x[1] = CHACHA_CONST[1];
	x[2] = CHACHA_CONST[2];
	x[3] = CHACHA_CONST[3];

	for (int word = 0; word < 8; ++word) {
		x[word + 4] = read32(key + (4 * word));
	}

	x[12] = (u32)block_counter;
	x[13] = (u32)(block_counter >> 32);
	x[14] = (u32)public_msg_num;
	x[15] = (u32)(public_msg_num >> 32);

	for (int round = CHACHA_ROUNDS; round > 0; round -= 2) {
		QUARTERROUND(0, 4, 8,  12)
		QUARTERROUND(1, 5, 9,  13)
		QUARTERROUND(2, 6, 10, 14)
		QUARTERROUND(3, 7, 11, 15)
		QUARTERROUND(0, 5, 10, 15)
		QUARTERROUND(1, 6, 11, 12)
		QUARTERROUND(2, 7, 8,  13)
		QUARTERROUND(3, 4, 9,  14)
	}

	x[0] += CHACHA_CONST[0];
	x[1] += CHACHA_CONST[1];
	x[2] += CHACHA_CONST[2];
	x[3] += CHACHA_CONST[3];

	for (int word = 0; word < 8; ++word) {
		x[word + 4] += read32(key + (4 * word));
	}

	x[12] += (u32)block_counter;
	x[13] += (u32)(block_counter >> 32);
	x[14] += (u32)public_msg_num;
	x[15] += (u32)(public_msg_num >> 32);
}

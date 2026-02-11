chacha(const unsigned char *key ,
			const unsigned char *public_msg_num_p ,
			const unsigned char *input,
			unsigned long long len,
			unsigned char *output)
{
	const u64 public_msg_num = read64(public_msg_num_p);
	u64 block_counter = 0;
	u32 keystream[16];

	while (len >= 64) {
		chacha_gen(key, block_counter, public_msg_num, keystream);

		for (int word = 0; word < 16; ++word, input += 4, output += 4) {
			write32(output, read32(input) ^ keystream[word]);
		}

		++block_counter;
		len -= 64;
	}

	if (len > 0) {
		chacha_gen(key, block_counter, public_msg_num, keystream);

		u64 words = len / 4;
		for (u64 word = 0; word < words; ++word, input += 4, output += 4) {
			write32(output, read32(input) ^ keystream[word]);
		}

		const u32 keystream_final = keystream[words];

		switch (len % 4) {
		case 3:	output[2] = input[2] ^ (u8)(keystream_final >> 16);
		case 2:	output[1] = input[1] ^ (u8)(keystream_final >> 8);
		case 1:	output[0] = input[0] ^ (u8)keystream_final;
		}
	}
}

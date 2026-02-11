tea_test(void)
{
	tea_key_t key;
	tea_block_t value;
	tea_block_t encrypted;
	tea_block_t decrypted;
	int i;
	char in[80];
	char out[80];
	char recovered[80];

	STATIC_ASSERT(sizeof(key.v) == TEA_KEY_SIZE);
	STATIC_ASSERT(sizeof(value.v) == TEA_BLOCK_SIZE);

	for (i = 0; i < 10; i++) {
		int j;
		bool randomized = FALSE;

		for (j = 0; j < 10; j++) {
			random_bytes(key.v, TEA_KEY_SIZE);
			random_bytes(value.v, TEA_BLOCK_SIZE);

			t_encrypt(&encrypted, &key, &value);
			if (0 != memcmp(value.v, encrypted.v, TEA_BLOCK_SIZE)) {
				randomized = TRUE;
				break;
			}
		}

		if (!randomized)
			g_error("no luck with random numbers in tea_test()");

		t_decrypt(&decrypted, &key, &encrypted);
		if (0 != memcmp(value.v, decrypted.v, TEA_BLOCK_SIZE)) {
			g_error("TEA implementation tests FAILED");
			return;
		}
	}

	STATIC_ASSERT(sizeof in == sizeof out);
	STATIC_ASSERT(sizeof in == sizeof recovered);

	random_bytes(key.v, TEA_KEY_SIZE);
	random_bytes(in, sizeof in);
	tea_encrypt(&key, out, in, sizeof in);
	tea_decrypt(&key, recovered, out, sizeof out);

	if (0 != memcmp(in, recovered, sizeof in))
		g_error("TEA implementation tests FAILED");
}

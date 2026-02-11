prf_test(gconstpointer data)
{
	const struct prf_data *test = data;
	unsigned int prf_len;
	unsigned char output[512];
	char prf[128];
	unsigned int i;
	int result;

	prf_len = strlen(test->prf) / 2;

	if (g_test_verbose() == TRUE) {
		g_print("PRF    = %s (%d octects)\n", test->prf, prf_len);
	}

	result = prf_sha1(test->key, test->key_len, test->prefix,
				test->prefix_len, test->data, test->data_len,
						output, prf_len);

	g_assert(result == 0);

	for (i = 0; i < prf_len; i++)
		sprintf(prf + (i * 2), "%02x", output[i]);

	if (g_test_verbose() == TRUE) {
		g_print("Result = %s\n", prf);
	}

	g_assert(strcmp(test->prf, prf) == 0);
}

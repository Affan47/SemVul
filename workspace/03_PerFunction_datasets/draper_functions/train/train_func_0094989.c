pbkdf2_test(gconstpointer data)
{
	const struct pbkdf2_data *test = data;
	unsigned int password_len;
	unsigned int salt_len;
	unsigned int key_len;
	unsigned char output[25];
	char key[50];
	unsigned int i;
	int result;

	password_len = test->password_len ? : strlen(test->password);
	salt_len = test->salt_len ? : strlen(test->salt);

	key_len = test->key_len ? : (strlen(test->key) / 2);

	if (g_test_verbose() == TRUE) {
		g_print("Password = \"%s\" (%d octects)\n",
					test->password, password_len);
		g_print("Salt     = \"%s\" (%d octects)\n",
					test->salt, salt_len);
		g_print("Count    = %d\n", test->count);
		g_print("Key      = %s (%d octects)\n", test->key, key_len);
	}

	result = pbkdf2_sha1(test->password, password_len,
					test->salt, salt_len,
					test->count, output, key_len);

	g_assert(result == 0);

	for (i = 0; i < key_len; i++)
		sprintf(key + (i * 2), "%02x", output[i]);

	if (g_test_verbose() == TRUE) {
		g_print("Result   = %s\n", key);
	}

	g_assert(strcmp(test->key, key) == 0);
}

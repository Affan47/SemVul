crypt_all(int *pcount, struct db_salt *salt)
{
	int count = *pcount;

	if (keys_mode != saved_salt.subtype) {
		int i;

		keys_mode = saved_salt.subtype;
		sign_extension_bug = (keys_mode == 'x');
		for (i = 0; i < count; i++)
			BF_std_set_key(saved_key[i], i, sign_extension_bug);
	}

	BF_std_crypt(&saved_salt, count);

	return count;
}

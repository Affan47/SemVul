BF_std_get_salt(char *ciphertext)
{
	static BF_salt salt;

	BF_decode(salt.salt, &ciphertext[7], 16);
	BF_swap(salt.salt, 4);

	salt.rounds = atoi(&ciphertext[4]);
	if (ciphertext[2] == 'a')
		salt.subtype = 'y';
	else
		salt.subtype = ciphertext[2];

	return &salt;
}

BF_std_crypt_exact(int index)
{
	BF_word L, R;
	BF_word u1, u2, u3, u4;
	BF_word count;
	int i;

	memcpy(&BF_out[index][2], &BF_magic_w[2], sizeof(BF_word) * 4);

	count = 64;
	do
	for (i = 2; i < 6; i += 2) {
		L = BF_out[index][i];
		R = BF_out[index][i + 1];
		BF_ENCRYPT(BF_current INDEX, L, R);
		BF_out[index][i] = L;
		BF_out[index][i + 1] = R;
	} while (--count);


	BF_out[index][5] &= ~(BF_word)0xFF;
}

base64_init(void)
{
	int x;
	memset(b2a, -1, sizeof(b2a));

	for (x = 0; x < 26; x++) {

		base64[x] = 'A' + x;
		b2a['A' + x] = x;

		base64[x + 26] = 'a' + x;
		b2a['a' + x] = x + 26;

		if (x < 10) {
			base64[x + 52] = '0' + x;
			b2a['0' + x] = x + 52;
		}
	}
	base64[62] = '+';
	base64[63] = '/';
	b2a[(int)'+'] = 62;
	b2a[(int)'/'] = 63;
}

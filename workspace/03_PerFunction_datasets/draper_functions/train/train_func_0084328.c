gen_pw(int sz)
{
	int i;
	char *buf = smalloc(sz + 1);

	for (i = 0; i < sz; i++)
	{
		buf[i] = ch[arc4random() % 26];
	}

	buf[sz] = 0;

	return buf;
}

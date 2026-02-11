b64encode(const QByteArray &s)
{
	int i;
	int len = s.size();
	static char tbl[] =
		"ABCDEFGH"
		"IJKLMNOP"
		"QRSTUVWX"
		"YZabcdef"
		"ghijklmn"
		"opqrstuv"
		"wxyz0123"
		"456789+/"
		"=";
	int a, b, c;

	QByteArray p((len + 2) / 3 * 4, 0);
	int at = 0;
	for(i = 0; i < len; i += 3)
	{
		a = ((unsigned char)s[i] & 3) << 4;
		if(i + 1 < len)
		{
			a += (unsigned char)s[i + 1] >> 4;
			b = ((unsigned char)s[i + 1] & 0xf) << 2;
			if(i + 2 < len)
			{
				b += (unsigned char)s[i + 2] >> 6;
				c = (unsigned char)s[i + 2] & 0x3f;
			}
			else
				c = 64;
		}
		else
			b = c = 64;

		p[at++] = tbl[(unsigned char)s[i] >> 2];
		p[at++] = tbl[a];
		p[at++] = tbl[b];
		p[at++] = tbl[c];
	}
	return p;
}

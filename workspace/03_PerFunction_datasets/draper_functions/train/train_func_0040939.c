encword(string w)
{
	string ww="";

	string::iterator b=w.begin(), e=w.end(), c;

	while (b != e)
	{
		for (c=b; c != e; c++)
			if ( *c == '@' || *c == '/' || *c == '%' || *c == ':')
				break;

		ww.append(b, c);

		b=c;

		if (b != e)
		{
			ww += '%';
			ww += x[ (*b / 16) & 15 ];
			ww += x[ *b & 15];
			b++;
		}
	}

	return ww;
}

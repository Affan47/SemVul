upper(string &w)
{
	for (string::iterator b=w.begin(), e=w.end(); b != e; ++b)
		if (*b >= 'a' && *b <= 'z')
			*b += 'A'-'a';
}

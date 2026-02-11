jdns_domain_cmp(const unsigned char *a, const unsigned char *b)
{
	int n;
	int len_a;


	len_a = _ustrlen(a);
	if(len_a != (int)_ustrlen(b))
		return 0;

	for(n = 0; n < len_a; ++n)
	{
		if(tolower(a[n]) != tolower(b[n]))
			return 0;
	}
	return 1;
}

AppendDNSNameString(domainname *const name, const char *cstr)
	{
	mDNSu8       *      ptr = name->c + DomainNameLength(name) - 1;
	const mDNSu8 *const lim = name->c + MAX_DOMAIN_NAME - 1;
	while (*cstr && ptr < lim)
		{
		mDNSu8 *lengthbyte = ptr++;
		while (*cstr && *cstr != '.' && ptr < lim)
			{
			mDNSu8 c = (mDNSu8)*cstr++;
			if (c == '\\')
				{
				if (*cstr == '\\' || *cstr == '.')
					c = (mDNSu8)*cstr++;
				else if (mdnsIsDigit(cstr[0]) && mdnsIsDigit(cstr[1]) && mdnsIsDigit(cstr[2]))
					{
					int v0 = cstr[0] - '0';
					int v1 = cstr[1] - '0';
					int v2 = cstr[2] - '0';
					int val = v0 * 100 + v1 * 10 + v2;
					if (val <= 255) { c = (mDNSu8)val; cstr += 3; }
					}
				}
			*ptr++ = c;
			}
		if (*cstr) cstr++;
		if (ptr - lengthbyte - 1 > MAX_DOMAIN_LABEL)
			return(mDNSNULL);
		*lengthbyte = (mDNSu8)(ptr - lengthbyte - 1);
		}

	*ptr++ = 0;
	if (*cstr) return(mDNSNULL);
	else return(ptr);
	}

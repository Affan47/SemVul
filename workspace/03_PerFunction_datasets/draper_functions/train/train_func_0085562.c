putDomainNameAsLabels(const DNSMessage *const msg,
	mDNSu8 *ptr, const mDNSu8 *const limit, const domainname *const name)
	{
	const mDNSu8 *const base        = (const mDNSu8 *)msg;
	const mDNSu8 *      np          = name->c;
	const mDNSu8 *const max         = name->c + MAX_DOMAIN_NAME;
	const mDNSu8 *      pointer     = mDNSNULL;
	const mDNSu8 *const searchlimit = ptr;

	while (*np && ptr < limit-1)
		{
		if (*np > MAX_DOMAIN_LABEL)
			{ LogMsg("Malformed domain name %##s (label more than 63 bytes)", name->c); return(mDNSNULL); }


		if (np + 1 + *np >= max)
			{ LogMsg("Malformed domain name %##s (more than 255 bytes)", name->c); return(mDNSNULL); }

		if (base) pointer = FindCompressionPointer(base, searchlimit, np);
		if (pointer)
			{
			mDNSu16 offset = (mDNSu16)(pointer - base);
			*ptr++ = (mDNSu8)(0xC0 | (offset >> 8));
			*ptr++ = (mDNSu8)(        offset      );
			return(ptr);
			}
		else
			{
			int i;
			mDNSu8 len = *np++;
			if (ptr + 1 + len >= limit) return(mDNSNULL);
			*ptr++ = len;
			for (i=0; i<len; i++) *ptr++ = *np++;
			}
		}

	if (ptr < limit)
		{
		*ptr++ = 0;
		return(ptr);
		}

	return(mDNSNULL);
	}

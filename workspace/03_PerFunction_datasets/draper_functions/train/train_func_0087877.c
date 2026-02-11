matchlabel(const unsigned char *a, int asize, const unsigned char *b, int bsize, const unsigned char *ref, int refsize, int ahopsleft, int bhopsleft)
{
	int n, alen, blen, offset;


	if(a == b)
		return 1;

	if(asize < 1 || bsize < 1)
		return 0;


	if(*a & 0xc0)
	{
		if(asize < 2)
			return 0;
		offset = getoffset(a, refsize, &ahopsleft);
		if(offset == -1)
			return 0;
		return matchlabel(ref + offset, refsize - offset, b, bsize, ref, refsize, ahopsleft, bhopsleft);
	}
	if(*b & 0xc0)
	{
		if(bsize < 2)
			return 0;
		offset = getoffset(b, refsize, &bhopsleft);
		if(offset == -1)
			return 0;
		return matchlabel(a, asize, ref + offset, refsize - offset, ref, refsize, ahopsleft, bhopsleft);
	}

	alen = *a & 0x3f;
	blen = *b & 0x3f;


	if(alen != blen)
		return 0;


	if(alen == 0)
		return 1;


	if(asize < alen + 2)
		return 0;
	if(bsize < blen + 2)
		return 0;


	for(n = 1; n < alen + 1; ++n)
	{
		if(a[n] != b[n])
			return 0;
	}


	n = alen + 1;
	return matchlabel(a + n, asize - n, b + n, bsize - n, ref, refsize, ahopsleft, bhopsleft);
}

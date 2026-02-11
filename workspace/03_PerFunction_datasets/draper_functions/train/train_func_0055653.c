Apply(BitString *b,int (*Applyfn)(int,void *),void *arg)
{
	size_t i,bytepos,bitpos;

	if (b == NULL)
		return NullPtrError("Apply");
	for (i=0; i<b->count;i++) {
		bytepos = (i/CHAR_BIT);
		bitpos = i & (CHAR_BIT-1);
		Applyfn(b->contents[bytepos]&(1 << bitpos),arg);
	}
	return 1;
}

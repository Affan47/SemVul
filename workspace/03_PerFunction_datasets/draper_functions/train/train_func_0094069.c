copy(Blk *hptr, int size)
{
	Blk *hdr;
	unsigned sz;
	char *ptr;

	all++;
	lall++;
	lcopy++;
	nbytes += size;
	lbytes += size;
	if(size > longest)
		longest = size;
	if(size > maxsize)
		maxsize = size;
	sz = length(hptr);
	ptr = malloc(size);
	if(ptr == 0) {
		Bprint(&bout,"copy size %d\n",size);
		ospace("copy");
	}
	memmove(ptr, hptr->beg, sz);
	memset(ptr+sz, 0, size-sz);
	if((hdr = hfree) == 0)
		hdr = morehd();
	hfree = (Blk *)hdr->rd;
	hdr->rd = hdr->beg = ptr;
	hdr->last = ptr+size;
	hdr->wt = ptr+sz;
	ptr = hdr->wt;
	while(ptr<hdr->last)
		*ptr++ = '\0';
	return(hdr);
}

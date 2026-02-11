__free_ovflpage(HTAB *hashp, BUFHEAD *obufp)
{
	uint16 addr;
	uint32 *freep;
	uint32 bit_address, free_page, free_bit;
	uint16 ndx;

	if(!obufp || !obufp->addr)
	    return;

	addr = obufp->addr;
#ifdef DEBUG1
	(void)fprintf(stderr, "Freeing %d\n", addr);
#endif
	ndx = (((uint16)addr) >> SPLITSHIFT);
	bit_address =
	    (ndx ? hashp->SPARES[ndx - 1] : 0) + (addr & SPLITMASK) - 1;
	if (bit_address < (uint32)hashp->LAST_FREED)
		hashp->LAST_FREED = bit_address;
	free_page = (bit_address >> (hashp->BSHIFT + BYTE_SHIFT));
	free_bit = bit_address & ((hashp->BSIZE << BYTE_SHIFT) - 1);

	if (!(freep = hashp->mapp[free_page]))
		freep = fetch_bitmap(hashp, free_page);

#ifdef DEBUG


	if (!freep)
	  {
		assert(0);
		return;
	  }
#endif
	CLRBIT(freep, free_bit);
#ifdef DEBUG2
	(void)fprintf(stderr, "FREE_OVFLPAGE: ADDR: %d BIT: %d PAGE %d\n",
	    obufp->addr, free_bit, free_page);
#endif
	__reclaim_buf(hashp, obufp);
}

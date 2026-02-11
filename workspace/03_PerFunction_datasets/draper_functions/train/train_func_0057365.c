alloc_size(void *pool, unsigned long poolsize, void *p)
{
	struct header *head = pool;
	unsigned int pgnum, sp_bits;
	unsigned long offset = (char *)p - (char *)pool;
	struct page_header *ph;

	if (poolsize < MIN_USEFUL_SIZE)
		return tiny_alloc_size(pool, poolsize, p);


	sp_bits = small_page_bits(poolsize);
	pgnum = offset >> sp_bits;


	if (test_bit(head->pagesize, pgnum >> BITS_FROM_SMALL_TO_LARGE_PAGE))
		pgnum &= ~(SMALL_PAGES_PER_LARGE_PAGE - 1);


	ph = from_pgnum(head, pgnum, sp_bits);
	if ((void *)ph == p)
		return huge_size(head, p);

	return bucket_to_size(ph->bucket);
}

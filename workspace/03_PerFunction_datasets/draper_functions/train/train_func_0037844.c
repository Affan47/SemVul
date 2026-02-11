mem_malloc_block(MemChunk *mc, size_t need)
{
  MemHeader *mh;
  MemBlockHeader *head_mbh, *mbh, *new_mbh;

  mh = (MemHeader *) mc->mem;
  head_mbh = (MemBlockHeader *) &mh->bogus;


  for (mbh = head_mbh; mbh != NULL; mbh = MBH_PTR(mh, mbh->next_offset)) {
	if (mbh->inuse || (mbh->dsize + MemBlockHeaderSize()) < need)
	  continue;

	if ((mbh->dsize + MemBlockHeaderSize()) == need) {
	  mbh->inuse = 1;
	  mc->avail -= need;
	  return((void *) &mbh->bogus);
	}


	if (mbh->dsize < need)
	  continue;


	new_mbh = (MemBlockHeader *) ((char *) mbh + need);
	new_mbh->dsize = mbh->dsize - need;
	new_mbh->next_offset = mbh->next_offset;
	new_mbh->prev_offset = MBH_OFFSET(mh, mbh);
	mbh->dsize = need - MemBlockHeaderSize();
	mbh->next_offset = MBH_OFFSET(mh, new_mbh);
	if (new_mbh->next_offset) {
	  MemBlockHeader *next_mbh;

	  next_mbh = MBH_PTR(mh, new_mbh->next_offset);
	  next_mbh->prev_offset = MBH_OFFSET(mh, new_mbh);
	}
	else
	  mh->tail_offset = MBH_OFFSET(mh, new_mbh);
	new_mbh->inuse = 0;
	mbh->mc = mc;
	mbh->inuse = 1;
	mc->avail -= need;
	return((void *) ((char *) mbh + MemBlockHeaderSize()));
  }


  return(NULL);
}

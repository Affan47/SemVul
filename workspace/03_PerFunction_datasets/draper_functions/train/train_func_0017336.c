__get_buf(HTAB *hashp, uint32 addr, BUFHEAD *prev_bp, int newpage)

{
	register BUFHEAD *bp;
	register uint32 is_disk_mask;
	register int is_disk, segment_ndx = 0;
	SEGMENT segp = 0;

	is_disk = 0;
	is_disk_mask = 0;
	if (prev_bp) {
		bp = prev_bp->ovfl;
		if (!bp || (bp->addr != addr))
			bp = NULL;
		if (!newpage)
			is_disk = BUF_DISK;
	} else {

		segment_ndx = addr & (hashp->SGSIZE - 1);


		segp = hashp->dir[addr >> hashp->SSHIFT];
#ifdef DEBUG
		assert(segp != NULL);
#endif

		bp = PTROF(segp[segment_ndx]);

		is_disk_mask = ISDISK(segp[segment_ndx]);
		is_disk = is_disk_mask || !hashp->new_file;
	}

	if (!bp) {
		bp = newbuf(hashp, addr, prev_bp);
		if (!bp)
			return(NULL);
		if(__get_page(hashp, bp->page, addr, !prev_bp, is_disk, 0))
		  {

			if(prev_bp)
			  {


				prev_bp->ovfl = NULL;
			  }
			BUF_REMOVE(bp);
			free(bp->page);
			free(bp);
			return (NULL);
		  }

		if (!prev_bp)
		  {
#if 0


			segp[segment_ndx] =
			    (BUFHEAD *)((ptrdiff_t)bp | is_disk_mask);
#else


			bp->is_disk = is_disk_mask;
			segp[segment_ndx] = bp;
#endif
		  }
	} else {
		BUF_REMOVE(bp);
		MRU_INSERT(bp);
	}
	return (bp);
}

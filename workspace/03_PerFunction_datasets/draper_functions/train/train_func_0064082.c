release_unused_segments(mstate m)
{
  size_t released = 0;
  size_t nsegs = 0;
  msegmentptr pred = &m->seg;
  msegmentptr sp = pred->next;
  while (sp != 0) {
    char *base = sp->base;
    size_t size = sp->size;
    msegmentptr next = sp->next;
    nsegs++;
    {
      mchunkptr p = align_as_chunk(base);
      size_t psize = chunksize(p);

      if (!cinuse(p) && (char *)p + psize >= base + size - TOP_FOOT_SIZE) {
	tchunkptr tp = (tchunkptr)p;
	if (p == m->dv) {
	  m->dv = 0;
	  m->dvsize = 0;
	} else {
	  unlink_large_chunk(m, tp);
	}
	if (CALL_MUNMAP(base, size) == 0) {
	  released += size;

	  sp = pred;
	  sp->next = next;
	} else {
	  insert_large_chunk(m, tp, psize);
	}
      }
    }
    pred = sp;
    sp = next;
  }

  m->release_checks = nsegs > MAX_RELEASE_CHECK_RATE ?
		      nsegs : MAX_RELEASE_CHECK_RATE;
  return released;
}

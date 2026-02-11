add_segment(mstate m, char* tbase, size_t tsize, flag_t mmapped) {

  char* old_top = (char*)m->top;
  msegmentptr oldsp = segment_holding(m, old_top);
  char* old_end = oldsp->base + oldsp->size;
  size_t ssize = pad_request(sizeof(struct malloc_segment));
  char* rawsp = old_end - (ssize + FOUR_SIZE_T_SIZES + CHUNK_ALIGN_MASK);
  size_t offset = align_offset(chunk2mem(rawsp));
  char* asp = rawsp + offset;
  char* csp = (asp < (old_top + MIN_CHUNK_SIZE))? old_top : asp;
  mchunkptr sp = (mchunkptr)csp;
  msegmentptr ss = (msegmentptr)(chunk2mem(sp));
  mchunkptr tnext = chunk_plus_offset(sp, ssize);
  mchunkptr p = tnext;
  int nfences = 0;


  init_top(m, (mchunkptr)tbase, tsize - TOP_FOOT_SIZE);


  assert(is_aligned(ss));
  set_size_and_pinuse_of_inuse_chunk(m, sp, ssize);
  *ss = m->seg;
  m->seg.base = tbase;
  m->seg.size = tsize;
  m->seg.sflags = mmapped;
  m->seg.next = ss;


  for (;;) {
    mchunkptr nextp = chunk_plus_offset(p, SIZE_T_SIZE);
    p->head = FENCEPOST_HEAD;
    ++nfences;
    if ((char*)(&(nextp->head)) < old_end)
      p = nextp;
    else
      break;
  }
  assert(nfences >= 2);


  if (csp != old_top) {
    mchunkptr q = (mchunkptr)old_top;
    size_t psize = csp - old_top;
    mchunkptr tn = chunk_plus_offset(q, psize);
    set_free_with_pinuse(q, psize, tn);
    insert_chunk(m, q, psize);
  }

  check_top_chunk(m, m->top);
}

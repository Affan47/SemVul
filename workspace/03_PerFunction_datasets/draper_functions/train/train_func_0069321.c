init_top(mstate m, mchunkptr p, size_t psize)
{

  size_t offset = align_offset(chunk2mem(p));
  p = (mchunkptr)((char *)p + offset);
  psize -= offset;

  m->top = p;
  m->topsize = psize;
  p->head = psize | PINUSE_BIT;

  chunk_plus_offset(p, psize)->head = TOP_FOOT_SIZE;
  m->trim_check = DEFAULT_TRIM_THRESHOLD;
}

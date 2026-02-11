get_val_for_pos(GtCustomTrackGcContent *ctgc, unsigned long pos)
{
  unsigned long i,
                gc_count = 0,
                bases = 0;
  for (i=0;i<ctgc->windowsize;i++)
  {
    if (pos + i > ctgc->seqlen)
      return -1;
    if (ctgc->seq[pos+i] == 'g' || ctgc->seq[pos+i] == 'c'
         || ctgc->seq[pos+i] == 'G' || ctgc->seq[pos+i] == 'C')
    {
      gc_count++;
    }
    bases++;
  }
  return ((double) gc_count)/((double) MIN(ctgc->windowsize, bases));
}

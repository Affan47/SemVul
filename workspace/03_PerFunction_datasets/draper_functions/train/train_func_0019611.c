gt_radixsort_new(bool pairs,unsigned long maxlen)
{
  GtRadixsortinfo *radixsortinfo = gt_malloc(sizeof (*radixsortinfo));

  radixsortinfo->size = sizeof (*radixsortinfo);
  radixsortinfo->rbuf = gt_radixbuffer_new(pairs);
  radixsortinfo->size += gt_radixbuffer_size(radixsortinfo->rbuf);
  radixsortinfo->pairs = pairs;
  radixsortinfo->maxlen = maxlen;
  if (maxlen > 0)
  {
    if (pairs)
    {
      radixsortinfo->sortspace.ulongpairptr
        = gt_malloc(sizeof (*radixsortinfo->sortspace.ulongpairptr) * maxlen);
     radixsortinfo->size += sizeof (*radixsortinfo->sortspace.ulongpairptr)
                            * maxlen;
    } else
    {
      radixsortinfo->sortspace.ulongptr
        = gt_malloc(sizeof (*radixsortinfo->sortspace.ulongptr) * maxlen);
      radixsortinfo->size += sizeof (*radixsortinfo->sortspace.ulongptr)
                             * maxlen;
    }
  }
  GT_STACK_INIT(&radixsortinfo->stack,32UL);
  radixsortinfo->size += sizeof (radixsortinfo->stack);
#ifdef GT_THREADS_ENABLED
  {
    const unsigned int threads = GT_THREADS_JOBS;

    if (threads > 1U)
    {
      unsigned int t;
      radixsortinfo->lentab
        = gt_malloc(sizeof (*radixsortinfo->lentab) * (UINT8_MAX+1));
      radixsortinfo->size += sizeof (*radixsortinfo->lentab) * (UINT8_MAX+1);
      radixsortinfo->endindexes
        = gt_malloc(sizeof (*radixsortinfo->endindexes) * threads);
      radixsortinfo->size += sizeof (*radixsortinfo->endindexes) * threads;
      radixsortinfo->threadinfo
        = gt_malloc(sizeof (*radixsortinfo->threadinfo) * threads);
      radixsortinfo->size += sizeof (*radixsortinfo->threadinfo) * threads;
      for (t = 0; t < threads; t++)
      {
        GT_STACK_INIT(&radixsortinfo->threadinfo[t].stack,32UL);
        radixsortinfo->size += sizeof (radixsortinfo->threadinfo[t].stack);
        radixsortinfo->threadinfo[t].rbuf = gt_radixbuffer_new(pairs);
        radixsortinfo->size
          += gt_radixbuffer_size(radixsortinfo->threadinfo[t].rbuf);
      }
    }
  }
#endif
  return radixsortinfo;
}

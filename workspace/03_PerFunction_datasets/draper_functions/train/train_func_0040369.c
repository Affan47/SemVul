gt_nextSequentialsuftabvalue(unsigned long *currentsuffix,
                                 Sequentialsuffixarrayreader *ssar)
{
  if (ssar->seqactype == SEQ_scan)
  {
#ifdef _LP64
    if (ssar->suffixarray->suftabstream_GtUlong.fp != NULL)
    {
      return gt_readnextfromstream_GtUlong(currentsuffix,
                                 &ssar->suffixarray->suftabstream_GtUlong);
    } else
    {
      uint32_t readvalue = 0;
      int ret = gt_readnextfromstream_uint32_t(
                                 &readvalue,
                                 &ssar->suffixarray->suftabstream_uint32_t);
      *currentsuffix = (unsigned long) readvalue;
      return ret;
    }
#else
     return gt_readnextfromstream_GtUlong(currentsuffix,
                                      &ssar->suffixarray->suftabstream_GtUlong);
#endif
  }
  if (ssar->seqactype == SEQ_mappedboth)
  {
    *currentsuffix = ESASUFFIXPTRGET(ssar->suffixarray->suftab,
                                     ssar->nextsuftabindex++);
    return 1;
  }
  *currentsuffix = ESASUFFIXPTRGET(ssar->suftab,ssar->nextsuftabindex++);
  return 1;
}

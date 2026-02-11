gt_sfimarkprefixsuffixbuckets(void *processinfo,
                                          GT_UNUSED bool firstinrange,
                                          GT_UNUSED unsigned long pos,
                                          GtCodetype scancode)
{
  Sfxiterator *sfi = (Sfxiterator *) processinfo;
  GtCodetype checkcode = GT_SCANCODE_TO_PREFIXCODE(sfi,scancode);

  gt_assert(firstinrange);
  if (!GT_ISIBITSET(sfi->markprefixbuckets,checkcode))
  {
    GT_SETIBIT(sfi->markprefixbuckets,checkcode);
  }
#ifdef _LP64
  checkcode = GT_SCANCODE_TO_SUFFIXCODE(sfi,scancode);
  if (!GT_ISIBITSET(sfi->marksuffixbuckets,checkcode))
  {
    GT_SETIBIT(sfi->marksuffixbuckets,checkcode);
  }
#endif
}

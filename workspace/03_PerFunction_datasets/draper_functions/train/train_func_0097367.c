gt_suftabSequentialsuffixarrayreader(
                        const Sequentialsuffixarrayreader *ssar)
{
  gt_assert(ssar->seqactype != SEQ_scan);
  if (ssar->seqactype == SEQ_mappedboth)
  {
    return ssar->suffixarray->suftab;
  }
  return ssar->suftab;
}

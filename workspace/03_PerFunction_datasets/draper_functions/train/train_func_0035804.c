bwttab2file(Outfileinfo *outfileinfo,
                       const GtSuffixsortspace *suffixsortspace,
                       GtReadmode readmode,
                       unsigned long numberofsuffixes,
                       GT_UNUSED GtError *err)
{
  bool haserr = false;

  gt_error_check(err);
  if (outfileinfo->outfpbwttab != NULL)
  {
    unsigned long startpos, pos;
    GtUchar cc = 0;

    for (pos=0; pos < numberofsuffixes; pos++)
    {
      startpos = gt_suffixsortspace_getdirect(suffixsortspace,pos);
      if (startpos == 0)
      {
        cc = (GtUchar) UNDEFBWTCHAR;
      } else
      {
        if (outfileinfo->outfpbwttab != NULL)
        {

          cc = gt_encseq_get_encoded_char(outfileinfo->encseq,
                                          startpos - 1,
                                          readmode);
        }
      }
      if (outfileinfo->outfpbwttab != NULL)
      {
        gt_xfwrite(&cc,sizeof (GtUchar),(size_t) 1,outfileinfo->outfpbwttab);
      }
    }
  }
  return haserr ? -1 : 0;
}

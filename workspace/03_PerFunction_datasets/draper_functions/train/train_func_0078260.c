writefmascii(const char *indexname,
                        const Fmindex *fm,
                        const GtSpecialcharinfo *specialcharinfo,
                        bool storeindexpos,
                        GtError *err)
{
  FILE *fmafp;

  gt_error_check(err);
  fmafp = gt_fa_fopen_with_suffix(indexname,FMASCIIFILESUFFIX,"wb",err);
  if (fmafp == NULL)
  {
    return -1;
  }
  fprintf (fmafp, "bwtlength=%lu\n",
           fm->bwtlength);
  fprintf (fmafp, "longest=%lu\n",
                   fm->longestsuffixpos);
  fprintf (fmafp, "storeindexpos=%d\n", storeindexpos ? 1 : 0);
  fprintf (fmafp, "log2blocksize=%u\n", fm->log2bsize);
  fprintf (fmafp, "log2markdist=%u\n", fm->log2markdist);
  fprintf (fmafp, "specialcharacters=%lu\n",specialcharinfo->specialcharacters);
  fprintf (fmafp, "specialranges=%lu\n",specialcharinfo->specialranges);
  fprintf (fmafp, "realspecialranges=%lu\n",specialcharinfo->realspecialranges);
  fprintf (fmafp, "lengthofspecialprefix=%lu\n",
           specialcharinfo->lengthofspecialprefix);
  fprintf (fmafp, "lengthofspecialsuffix=%lu\n",
           specialcharinfo->lengthofspecialsuffix);
  fprintf (fmafp, "wildcards=%lu\n",specialcharinfo->wildcards);
  fprintf (fmafp, "wildcardranges=%lu\n",specialcharinfo->wildcardranges);
  fprintf (fmafp, "realwildcardranges=%lu\n",
                   specialcharinfo->realwildcardranges);
  fprintf (fmafp, "lengthofwildcardprefix=%lu\n",
           specialcharinfo->lengthofwildcardprefix);
  fprintf (fmafp, "lengthofwildcardsuffix=%lu\n",
           specialcharinfo->lengthofwildcardsuffix);
  fprintf (fmafp, "suffixlength=%u\n", fm->suffixlength);
  gt_fa_xfclose(fmafp);
  return 0;
}

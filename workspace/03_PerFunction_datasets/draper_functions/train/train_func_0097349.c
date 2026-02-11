gt_tyrcountinfo_new(const Tyrindex *tyrindex,
                                  const char *tyrindexname,
                                  GtError *err)
{
  size_t numofbytes;
  void *tmp;
  bool haserr = false;
  Tyrcountinfo *tyrcountinfo;

  gt_error_check(err);
  tyrcountinfo = gt_malloc(sizeof *tyrcountinfo);
  tyrcountinfo->indexfilename = tyrindexname;
  tyrcountinfo->mappedmctfileptr
    = gt_fa_mmap_read_with_suffix(tyrindexname,COUNTSSUFFIX,&numofbytes,err);
  if (tyrcountinfo->mappedmctfileptr == NULL)
  {
    tyrcountinfo->smallcounts = NULL;
    haserr = true;
  } else
  {
    tyrcountinfo->smallcounts
      = (GtUchar *) tyrcountinfo->mappedmctfileptr;
    tmp = &tyrcountinfo->smallcounts[tyrindex->numofmers];
    tyrcountinfo->largecounts = (Largecount *) tmp;
    if (numofbytes < tyrindex->numofmers)
    {
      gt_error_set(err,"size of file \"%s.%s\" is smaller than minimum size "
                       "%lu",tyrindexname,COUNTSSUFFIX,
                       (unsigned long) tyrindex->numofmers);
      haserr = true;
    }
  }
  if (!haserr && (numofbytes - tyrindex->numofmers) % sizeof (Largecount) != 0)
  {
    gt_error_set(err,"(numofbytes - numofmers) = %lu must be a multiple of %lu",
           (unsigned long) (numofbytes - tyrindex->numofmers),
           (unsigned long) sizeof (Largecount));
    haserr = true;
  }
  if (!haserr)
  {
    tyrcountinfo->numoflargecounts
      = (unsigned long) (numofbytes - tyrindex->numofmers)/
        (unsigned long) sizeof (Largecount);
  }
  if (haserr)
  {
    if (tyrcountinfo->mappedmctfileptr != NULL)
    {
      gt_fa_xmunmap(tyrcountinfo->mappedmctfileptr);
      tyrcountinfo->mappedmctfileptr = NULL;
    }
    gt_free(tyrcountinfo);
  }
  return haserr ? NULL : tyrcountinfo;
}

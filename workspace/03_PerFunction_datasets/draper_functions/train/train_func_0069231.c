gt_reads2twobit_collect_fileinfo(const GtReads2Twobit *r2t,
    GtFilelengthvalues **filelengthtab, GtStrArray **filenametab)
{
  unsigned long i, noflibraries;
  noflibraries = gt_array_size(r2t->collection);
  *filenametab = gt_str_array_new();
  if (filelengthtab != NULL)
  {
    *filelengthtab = gt_malloc(sizeof (**filelengthtab) * noflibraries);
  }
  for (i = 0; i < noflibraries; i++)
  {
    GtStr *libname;
    GtReadsLibraryInfo *rli;
    rli = gt_array_get(r2t->collection, i);
    if (filelengthtab != NULL)
    {
      (*filelengthtab)[i].effectivelength =
        (uint64_t)rli->total_seqlength - 1UL;
      if (r2t->seqlen_eqlen == 0 && i == noflibraries - 1UL)
        (*filelengthtab)[i].effectivelength--;
      (*filelengthtab)[i].length = (uint64_t)rli->total_filelength;
    }
    libname = gt_str_clone(rli->filename1);
    if (rli->filename2 != NULL)
    {
      gt_str_append_char(libname, GT_READS2TWOBIT_LIBSPECSEP);
      gt_str_append_str(libname, rli->filename2);
    }
    if (rli->paired)
    {
      gt_str_append_char(libname, GT_READS2TWOBIT_LIBSPECSEP);
      gt_str_append_ulong(libname, rli->insertlength);
      if (rli->stdev > 0)
      {
        gt_str_append_char(libname, GT_READS2TWOBIT_INSERTSEP);
        gt_str_append_ulong(libname, rli->stdev);
      }
    }
    gt_str_array_add(*filenametab, libname);
    gt_str_delete(libname);
  }
}

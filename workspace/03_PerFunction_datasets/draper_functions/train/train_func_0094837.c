gt_Sfxmappedrange_usetmp(GtSfxmappedrange *sfxmappedrange,
                              const GtStr *tmpfilename,
                              void **usedptrptr,
                              unsigned long numofentries,
                              bool writable)
{
  gt_assert(sfxmappedrange != NULL);
  sfxmappedrange->ptr = NULL;

  sfxmappedrange->usedptrptr = usedptrptr;
  sfxmappedrange->filename = gt_str_clone(tmpfilename);
  sfxmappedrange->writable = writable;
  if (sfxmappedrange->type == GtSfxGtBitsequence)
  {
    sfxmappedrange->numofunits = GT_NUMOFINTSFORBITS(numofentries);
  } else
  {
    sfxmappedrange->numofunits = (size_t) numofentries;
  }
  gt_log_log("use file %s for table %s (%lu units of %lu bytes)",
             gt_str_get(sfxmappedrange->filename),
             gt_str_get(sfxmappedrange->tablename),
             (unsigned long) sfxmappedrange->numofunits,
             (unsigned long) sfxmappedrange->sizeofunit);
  gt_free(*sfxmappedrange->usedptrptr);
  *sfxmappedrange->usedptrptr = NULL;
}

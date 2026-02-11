hi_search_exec(hi_file *file,
                               off_t begin_offset,
                               off_t *found_offset,
                               pcre *re)
{
  int rc;
  int ovector[OVECCOUNT];
  rc = pcre_exec(re, NULL, (const char *)file->memory, file->size, begin_offset, 0,
                 ovector, OVECCOUNT);
  if (rc < 0)
  {
    VDPRINTF("Could not find due to %i\n", rc);
    return FALSE;
  }
  *found_offset = ovector[0];
  VDPRINTF("Found at %i\n", *found_offset);
  return TRUE;
}

cpio_append_fts_entry (FTSENT *entry)
{
  if (entry->fts_info & FTS_NS || entry->fts_info & FTS_NSOK)
    cpio_append (entry->fts_path);
  else
    cpio_append_stat (entry->fts_path, entry->fts_statp);
}

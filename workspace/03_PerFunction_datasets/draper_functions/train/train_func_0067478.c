dir_useless (Dir *d)
{
  if (d->doc == NULL)
    dir_load_doc (d, NULL);

  if (d->need_rescan_subdirs)
    dir_rescan_subdirs (d, NULL);

  return
    d->subdir_names == NULL &&
    g_hash_table_size (d->entry_cache) == 0;
}

cache_sync (Cache    *cache,
            GError  **err)
{
  SyncData sd = { FALSE, NULL, FALSE };
  GSList *list;

  sd.dc = cache;

  gconf_log (GCL_DEBUG, "Syncing the dir cache");

 redo:
  sd.failed = FALSE;
  sd.deleted_some = FALSE;


  list = NULL;
  g_hash_table_foreach (cache->cache, (GHFunc)listify_foreach, &list);


  list = g_slist_sort (list, dircmp);


  g_slist_foreach (list, (GFunc) cache_sync_foreach, &sd);
  g_slist_free (list);


  if (!sd.failed && sd.deleted_some)
    goto redo;

  if (sd.failed && err && *err == NULL)
    {
      gconf_set_error (err, GCONF_ERROR_FAILED,
		       _("Failed to sync XML cache contents to disk"));
    }

  return !sd.failed;
}

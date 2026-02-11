cache_clean_foreach(const gchar* key,
                    Dir* dir, CleanData* cd)
{
  GTime last_access;

  last_access = dir_get_last_access(dir);

  if ((cd->now - last_access) >= cd->length)
    {
      if (!dir_sync_pending(dir))
        {
          dir_destroy(dir);
          return TRUE;
        }
      else
        {
          gconf_log(GCL_WARNING, _("Unable to remove directory `%s' from the XML backend cache, because it has not been successfully synced to disk"),
                    dir_get_name(dir));
          return FALSE;
        }
    }
  else
    return FALSE;
}

unity_webapps_resource_db_ensure_within_size ()
{
  goffset size;

  size = get_resource_directory_size ();

  if (size < MAXIMUM_DIRECTORY_SIZE)
    {
      return;
    }
  else
    {
      UNITY_WEBAPPS_NOTE (RESOURCE, "Resource database too large, dropping LRU");
      db_drop_lru ();
    }
}

gst_registry_binary_cache_finish (BinaryRegistryCache * cache, gboolean success)
{

  if (success && fsync (cache->cache_fd) < 0)
    goto fsync_failed;

  if (close (cache->cache_fd) < 0)
    goto close_failed;

  if (!success)
    goto fail_after_close;


  if (g_rename (cache->tmp_location, cache->location) < 0) {
    GST_ERROR ("g_rename() failed: %s", g_strerror (errno));
    goto rename_failed;
  }

  g_free (cache->tmp_location);
  g_slice_free (BinaryRegistryCache, cache);
  GST_INFO ("Wrote binary registry cache");
  return TRUE;


fail_after_close:
  {
    g_unlink (cache->tmp_location);
    g_free (cache->tmp_location);
    g_slice_free (BinaryRegistryCache, cache);
    return FALSE;
  }
fsync_failed:
  {
    GST_ERROR ("fsync() failed: %s", g_strerror (errno));
    goto fail_after_close;
  }
close_failed:
  {
    GST_ERROR ("close() failed: %s", g_strerror (errno));
    goto fail_after_close;
  }
rename_failed:
  {
    GST_ERROR ("g_rename() failed: %s", g_strerror (errno));
    goto fail_after_close;
  }
}

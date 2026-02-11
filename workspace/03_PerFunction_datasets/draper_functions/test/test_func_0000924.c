dconf_mock_shm_reset (void)
{
  g_mutex_lock (&dconf_mock_shm_lock);
  if (dconf_mock_shm_table != NULL)
    {
      GHashTableIter iter;
      gpointer value;

      g_hash_table_iter_init (&iter, dconf_mock_shm_table);
      while (g_hash_table_iter_next (&iter, NULL, &value))
        {
          DConfMockShm *shm = value;

          g_assert_cmpint (shm->ref_count, ==, 1);
          g_hash_table_iter_remove (&iter);
        }

      g_string_truncate (dconf_mock_shm_log, 0);
    }
  g_mutex_unlock (&dconf_mock_shm_lock);
}

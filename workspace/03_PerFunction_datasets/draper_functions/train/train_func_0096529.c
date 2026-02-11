release_table_share(TABLE_SHARE *share)
{
  DBUG_ENTER("release_table_share");
  DBUG_PRINT("enter",
             ("share: 0x%lx  table: %s.%s  ref_count: %u  version: %lu",
              (ulong) share, share->db.str, share->table_name.str,
              share->ref_count, share->version));

  mysql_mutex_assert_owner(&LOCK_open);

  DBUG_ASSERT(share->ref_count);
  if (!--share->ref_count)
  {
    if (share->has_old_version() || table_def_shutdown_in_progress)
      my_hash_delete(&table_def_cache, (uchar*) share);
    else
    {

      DBUG_PRINT("info",("moving share to unused list"));

      DBUG_ASSERT(share->next == 0);
      share->prev= end_of_unused_share.prev;
      *end_of_unused_share.prev= share;
      end_of_unused_share.prev= &share->next;
      share->next= &end_of_unused_share;

      if (table_def_cache.records > table_def_size)
      {

        my_hash_delete(&table_def_cache, (uchar*) oldest_unused_share);
      }
    }
  }

  DBUG_VOID_RETURN;
}

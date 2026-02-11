get_share(const char *table_name)
{
  st_blackhole_share *share;
  uint length;

  length= (uint) strlen(table_name);
  mysql_mutex_lock(&blackhole_mutex);

  if (!(share= (st_blackhole_share*)
        my_hash_search(&blackhole_open_tables,
                       (uchar*) table_name, length)))
  {
    if (!(share= (st_blackhole_share*) my_malloc(sizeof(st_blackhole_share) +
                                                 length,
                                                 MYF(MY_WME | MY_ZEROFILL))))
      goto error;

    share->table_name_length= length;
    strmov(share->table_name, table_name);

    if (my_hash_insert(&blackhole_open_tables, (uchar*) share))
    {
      my_free(share);
      share= NULL;
      goto error;
    }

    thr_lock_init(&share->lock);
  }
  share->use_count++;

error:
  mysql_mutex_unlock(&blackhole_mutex);
  return share;
}

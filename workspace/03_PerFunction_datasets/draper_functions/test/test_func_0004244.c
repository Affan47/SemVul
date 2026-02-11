tdc_remove_table(THD *thd, enum_tdc_remove_table_type remove_type,
                      const char *db, const char *table_name,
                      bool has_lock)
{
  char key[MAX_DBKEY_LENGTH];
  uint key_length;
  TABLE *table;
  TABLE_SHARE *share;

  if (! has_lock)
    mysql_mutex_lock(&LOCK_open);
  else
  {
    mysql_mutex_assert_owner(&LOCK_open);
  }

  DBUG_ASSERT(remove_type == TDC_RT_REMOVE_UNUSED ||
              thd->mdl_context.is_lock_owner(MDL_key::TABLE, db, table_name,
                                             MDL_EXCLUSIVE));

  key_length= create_table_def_key(key, db, table_name);

  if ((share= (TABLE_SHARE*) my_hash_search(&table_def_cache,(uchar*) key,
                                            key_length)))
  {
    if (share->ref_count)
    {
      I_P_List_iterator<TABLE, TABLE_share> it(share->free_tables);
#ifndef DBUG_OFF
      if (remove_type == TDC_RT_REMOVE_ALL)
      {
        DBUG_ASSERT(share->used_tables.is_empty());
      }
      else if (remove_type == TDC_RT_REMOVE_NOT_OWN)
      {
        I_P_List_iterator<TABLE, TABLE_share> it2(share->used_tables);
        while ((table= it2++))
          if (table->in_use != thd)
          {
            DBUG_ASSERT(0);
          }
      }
#endif


      share->version= 0;

      while ((table= it++))
        free_cache_entry(table);
    }
    else
      (void) my_hash_delete(&table_def_cache, (uchar*) share);
  }

  if (! has_lock)
    mysql_mutex_unlock(&LOCK_open);
}

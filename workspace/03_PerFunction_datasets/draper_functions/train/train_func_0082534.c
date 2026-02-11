assign_new_table_id(TABLE_SHARE *share)
{

  DBUG_ENTER("assign_new_table_id");


  DBUG_ASSERT(share != NULL);
  mysql_mutex_assert_owner(&LOCK_open);

  ulong tid= ++last_table_id;


  if (unlikely(tid == ~0UL))
    tid= ++last_table_id;
  share->table_map_id= tid;
  DBUG_PRINT("info", ("table_id=%lu", tid));


  DBUG_ASSERT(share->table_map_id != ~0UL);

  DBUG_VOID_RETURN;
}

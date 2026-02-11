leave_locked_tables_mode()
{
  if (locked_tables_mode == LTM_LOCK_TABLES)
  {


    mdl_context.set_transaction_duration_for_all_locks();


    global_read_lock.set_explicit_lock_duration(this);

    if (handler_tables_hash.records)
      mysql_ha_set_explicit_lock_duration(this);
  }
  locked_tables_mode= LTM_NONE;
}

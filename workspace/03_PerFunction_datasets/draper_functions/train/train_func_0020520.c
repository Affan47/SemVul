cleanup_context(THD *thd, bool error)
{
  DBUG_ENTER("Relay_log_info::cleanup_context");

  DBUG_ASSERT(sql_thd == thd);


  if (error)
  {
    trans_rollback_stmt(thd);
    trans_rollback(thd);
  }
  m_table_map.clear_tables();
  slave_close_thread_tables(thd);
  if (error)
    thd->mdl_context.release_transactional_locks();
  clear_flag(IN_STMT);


  thd->variables.option_bits&= ~OPTION_NO_FOREIGN_KEY_CHECKS;
  thd->variables.option_bits&= ~OPTION_RELAXED_UNIQUE_CHECKS;


  reset_row_stmt_start_timestamp();
  unset_long_find_row_note_printed();

  DBUG_VOID_RETURN;
}

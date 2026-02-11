read_lock_type_for_table(THD *thd,
                                       Query_tables_list *prelocking_ctx,
                                       TABLE_LIST *table_list)
{


  bool log_on= mysql_bin_log.is_open() && thd->variables.sql_log_bin;
  ulong binlog_format= thd->variables.binlog_format;
  if ((log_on == FALSE) || (binlog_format == BINLOG_FORMAT_ROW) ||
      (table_list->table->s->table_category == TABLE_CATEGORY_LOG) ||
      (table_list->table->s->table_category == TABLE_CATEGORY_PERFORMANCE) ||
      !(is_update_query(prelocking_ctx->sql_command) ||
        table_list->prelocking_placeholder ||
        (thd->locked_tables_mode > LTM_LOCK_TABLES)))
    return TL_READ;
  else
    return TL_READ_NO_INSERT;
}

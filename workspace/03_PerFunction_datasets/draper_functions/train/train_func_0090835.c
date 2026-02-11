binlog_update_row(TABLE* table, bool is_trans,
                           MY_BITMAP const* cols, size_t colcnt,
                           const uchar *before_record,
                           const uchar *after_record)
{
  DBUG_ASSERT(is_current_stmt_binlog_format_row() && mysql_bin_log.is_open());

  size_t const before_maxlen = max_row_length(table, before_record);
  size_t const after_maxlen  = max_row_length(table, after_record);

  Row_data_memory row_data(table, before_maxlen, after_maxlen);
  if (!row_data.has_memory())
    return HA_ERR_OUT_OF_MEM;

  uchar *before_row= row_data.slot(0);
  uchar *after_row= row_data.slot(1);

  size_t const before_size= pack_row(table, cols, before_row,
                                        before_record);
  size_t const after_size= pack_row(table, cols, after_row,
                                       after_record);


#ifndef HAVE_purify
  DBUG_DUMP("before_record", before_record, table->s->reclength);
  DBUG_DUMP("after_record",  after_record, table->s->reclength);
  DBUG_DUMP("before_row",    before_row, before_size);
  DBUG_DUMP("after_row",     after_row, after_size);
#endif

  Rows_log_event* const ev=
    binlog_prepare_pending_rows_event(table, server_id, cols, colcnt,
				      before_size + after_size, is_trans,
				      static_cast<Update_rows_log_event*>(0));

  if (unlikely(ev == 0))
    return HA_ERR_OUT_OF_MEM;

  return
    ev->add_row_data(before_row, before_size) ||
    ev->add_row_data(after_row, after_size);
}

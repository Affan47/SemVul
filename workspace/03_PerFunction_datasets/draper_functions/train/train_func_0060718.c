repl_semi_slave_queue_event(Binlog_relay_IO_param *param,
				const char *event_buf,
				unsigned long event_len,
				uint32 flags)
{
  if (rpl_semi_sync_slave_status && semi_sync_need_reply)
  {


    (void) repl_semisync.slaveReply(param->mysql,
                                    param->master_log_name,
                                    param->master_log_pos);
  }
  return 0;
}

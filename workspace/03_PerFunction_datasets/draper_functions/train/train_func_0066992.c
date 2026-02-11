hibernate_go_dormant(time_t now)
{
  connection_t *conn;

  if (hibernate_state == HIBERNATE_STATE_DORMANT)
    return;
  else if (hibernate_state == HIBERNATE_STATE_LOWBANDWIDTH)
    hibernate_state = HIBERNATE_STATE_DORMANT;
  else
    hibernate_begin(HIBERNATE_STATE_DORMANT, now);

  log_notice(LD_ACCT,"Going dormant. Blowing away remaining connections.");


  while ((conn = connection_get_by_type(CONN_TYPE_OR)) ||
         (conn = connection_get_by_type(CONN_TYPE_AP)) ||
         (conn = connection_get_by_type(CONN_TYPE_EXIT))) {
    if (CONN_IS_EDGE(conn))
      connection_edge_end(TO_EDGE_CONN(conn), END_STREAM_REASON_HIBERNATING);
    log_info(LD_NET,"Closing conn type %d", conn->type);
    if (conn->type == CONN_TYPE_AP)
      connection_mark_unattached_ap(TO_ENTRY_CONN(conn),
                                    END_STREAM_REASON_HIBERNATING);
    else
      connection_mark_for_close(conn);
  }

  if (now < interval_wakeup_time)
    hibernate_end_time = interval_wakeup_time;
  else
    hibernate_end_time = interval_end_time;

  accounting_record_bandwidth_usage(now, get_or_state());

  or_state_mark_dirty(get_or_state(),
                      get_options()->AvoidDiskWrites ? now+600 : 0);
}

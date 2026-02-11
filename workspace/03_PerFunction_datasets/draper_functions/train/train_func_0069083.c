check_originator_id(THD *thd)
{

  if ((thd->system_thread == SYSTEM_THREAD_SLAVE_SQL) ||
      (thd->system_thread == SYSTEM_THREAD_SLAVE_IO))
  {
    DBUG_PRINT("info", ("Invoked object status set to SLAVESIDE_DISABLED."));
    if ((status == Event_parse_data::ENABLED) ||
        (status == Event_parse_data::DISABLED))
    {
      status= Event_parse_data::SLAVESIDE_DISABLED;
      status_changed= true;
    }
    originator = thd->server_id;
  }
  else
    originator = server_id;
}

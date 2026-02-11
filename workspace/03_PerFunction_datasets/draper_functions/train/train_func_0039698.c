start_handle_manager()
{
  DBUG_ENTER("start_handle_manager");
  abort_manager = false;
  if (flush_time && flush_time != ~(ulong) 0L)
  {
    pthread_t hThread;
    int error;
    if ((error= mysql_thread_create(key_thread_handle_manager,
                                    &hThread, &connection_attrib,
                                    handle_manager, 0)))
      sql_print_warning("Can't create handle_manager thread (errno= %d)",
                        error);
  }
  DBUG_VOID_RETURN;
}

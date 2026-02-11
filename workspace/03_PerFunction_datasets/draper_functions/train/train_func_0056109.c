execute_loop(String *expanded_query,
                                 bool open_cursor,
                                 uchar *packet,
                                 uchar *packet_end)
{
  const int MAX_REPREPARE_ATTEMPTS= 3;
  Reprepare_observer reprepare_observer;
  bool error;
  int reprepare_attempt= 0;


  if (state == Query_arena::STMT_ERROR)
  {
    my_message(last_errno, last_error, MYF(0));
    return TRUE;
  }

  if (set_parameters(expanded_query, packet, packet_end))
    return TRUE;

reexecute:
  reprepare_observer.reset_reprepare_observer();


  DBUG_ASSERT(thd->free_list == NULL);


  if (sql_command_flags[lex->sql_command] &
      CF_REEXECUTION_FRAGILE)
  {
    DBUG_ASSERT(thd->m_reprepare_observer == NULL);
    thd->m_reprepare_observer = &reprepare_observer;
  }

  error= execute(expanded_query, open_cursor) || thd->is_error();

  thd->m_reprepare_observer= NULL;

  if (error && !thd->is_fatal_error && !thd->killed &&
      reprepare_observer.is_invalidated() &&
      reprepare_attempt++ < MAX_REPREPARE_ATTEMPTS)
  {
    DBUG_ASSERT(thd->stmt_da->sql_errno() == ER_NEED_REPREPARE);
    thd->clear_error();

    error= reprepare();

    if (! error)
      goto reexecute;
  }
  reset_stmt_params(this);

  return error;
}

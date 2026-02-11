kill_delayed_threads_for_table(TABLE_SHARE *share)
{
  I_P_List_iterator<TABLE, TABLE_share> it(share->used_tables);
  TABLE *tab;

  mysql_mutex_assert_owner(&LOCK_open);

  while ((tab= it++))
  {
    THD *in_use= tab->in_use;

    if ((in_use->system_thread & SYSTEM_THREAD_DELAYED_INSERT) &&
        ! in_use->killed)
    {
      in_use->killed= THD::KILL_CONNECTION;
      mysql_mutex_lock(&in_use->mysys_var->mutex);
      if (in_use->mysys_var->current_cond)
      {
        mysql_mutex_lock(in_use->mysys_var->current_mutex);
        mysql_cond_broadcast(in_use->mysys_var->current_cond);
        mysql_mutex_unlock(in_use->mysys_var->current_mutex);
      }
      mysql_mutex_unlock(&in_use->mysys_var->mutex);
    }
  }
}

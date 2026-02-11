acquire_lock(MDL_request *mdl_request, ulong lock_wait_timeout)
{
  MDL_lock *lock;
  MDL_ticket *ticket;
  struct timespec abs_timeout;
  MDL_wait::enum_wait_status wait_status;

  set_timespec(abs_timeout, lock_wait_timeout);

  if (try_acquire_lock_impl(mdl_request, &ticket))
    return TRUE;

  if (mdl_request->ticket)
  {


    return FALSE;
  }


  lock= ticket->m_lock;


  if (lock->has_no_wait_context(this))
  {
    mysql_prlock_unlock(&lock->m_rwlock);
    MDL_ticket::destroy(ticket);
    my_message(ER_LOCK_ABORTED, ER_LOCK_ABORTED_MSG, MYF(0));
    return TRUE;
  }

  lock->m_waiting.add_ticket(ticket);


  m_wait.reset_status();

  if (lock->needs_notification(ticket))
    lock->notify_conflicting_locks(this);

  mysql_prlock_unlock(&lock->m_rwlock);

  will_wait_for(ticket);


  DEBUG_SYNC(m_thd, "mdl_acquire_lock_wait");

  find_deadlock();

  if (lock->needs_notification(ticket))
  {
    struct timespec abs_shortwait;
    set_timespec(abs_shortwait, 1);
    wait_status= MDL_wait::EMPTY;

    while (cmp_timespec(abs_shortwait, abs_timeout) <= 0)
    {

      wait_status= m_wait.timed_wait(m_thd, &abs_shortwait, FALSE,
                                     mdl_request->key.get_wait_state_name());

      if (wait_status != MDL_wait::EMPTY)
        break;

      mysql_prlock_wrlock(&lock->m_rwlock);
      lock->notify_conflicting_locks(this);
      mysql_prlock_unlock(&lock->m_rwlock);
      set_timespec(abs_shortwait, 1);
    }
    if (wait_status == MDL_wait::EMPTY)
      wait_status= m_wait.timed_wait(m_thd, &abs_timeout, TRUE,
                                     mdl_request->key.get_wait_state_name());
  }
  else
    wait_status= m_wait.timed_wait(m_thd, &abs_timeout, TRUE,
                                   mdl_request->key.get_wait_state_name());

  done_waiting_for();

  if (wait_status != MDL_wait::GRANTED)
  {
    lock->remove_ticket(&MDL_lock::m_waiting, ticket);
    MDL_ticket::destroy(ticket);
    switch (wait_status)
    {
    case MDL_wait::VICTIM:
      my_error(ER_LOCK_DEADLOCK, MYF(0));
      break;
    case MDL_wait::TIMEOUT:
      my_error(ER_LOCK_WAIT_TIMEOUT, MYF(0));
      break;
    case MDL_wait::KILLED:
      break;
    case MDL_wait::ABORTED:
      my_message(ER_LOCK_ABORTED, ER_LOCK_ABORTED_MSG, MYF(0));
      break;
    default:
      DBUG_ASSERT(0);
      break;
    }
    return TRUE;
  }


  lock->abort_conflicting_lock_requests();


  DBUG_ASSERT(wait_status == MDL_wait::GRANTED);

  m_tickets[mdl_request->duration].push_front(ticket);

  mdl_request->ticket= ticket;

  return FALSE;
}

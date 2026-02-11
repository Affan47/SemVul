spawn_n (size_t n,
                             ACE_THR_FUNC func,
                             void *args,
                             long flags,
                             long priority,
                             int grp_id,
                             ACE_Task_Base *task,
                             ACE_hthread_t thread_handles[],
                             void *stack[],
                             size_t stack_size[],
                             const char* thr_name[])
{
  ACE_TRACE ("ACE_Thread_Manager::spawn_n");
  ACE_MT (ACE_GUARD_RETURN (ACE_Thread_Mutex, ace_mon, this->lock_, -1));

  if (grp_id == -1)
    grp_id = this->grp_id_++;

  for (size_t i = 0; i < n; i++)
    {


      if (this->spawn_i (func,
                         args,
                         flags,
                         0,
                         thread_handles == 0 ? 0 : &thread_handles[i],
                         priority,
                         grp_id,
                         stack == 0 ? 0 : stack[i],
                         stack_size == 0 ? ACE_DEFAULT_THREAD_STACKSIZE : stack_size[i],
                         task,
                         thr_name == 0 ? 0 : &thr_name [i]) == -1)
        return -1;
    }

  return grp_id;
}

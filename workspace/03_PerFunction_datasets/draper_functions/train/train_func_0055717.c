unblock_from_queue (SCM queue)
{
  SCM thread = dequeue (queue);
  if (scm_is_true (thread))
    scm_i_pthread_cond_signal (&SCM_I_THREAD_DATA(thread)->sleep_cond);
  return thread;
}

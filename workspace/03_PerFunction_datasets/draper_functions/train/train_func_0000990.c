set_thr_exit (ACE_TSS_TYPE (ACE_Thread_Exit) *ptr)
{
  if (ACE_Thread_Manager::thr_exit_ == 0)
    ACE_Thread_Manager::thr_exit_ = ptr;
  else
    return -1;
  return 0;
}

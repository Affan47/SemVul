insert (ACE_Thread_Manager *tm, int insert)
{
  ACE_OS_TRACE ("ACE_Thread_Control::insert");

  ACE_hthread_t t_id;
  ACE_OS::thr_self (t_id);
  this->tm_ = tm;

  if (insert)
    return this->tm_->insert_thr (ACE_OS::thr_self (), t_id);
  else
    return 0;
}

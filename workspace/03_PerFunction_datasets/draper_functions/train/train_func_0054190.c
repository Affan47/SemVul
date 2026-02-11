sig_pending (int pending)
{
  ACE_TRACE ("ACE_Sig_Handler::sig_pending");

  ACE_MT (ACE_Recursive_Thread_Mutex *lock =
          ACE_Managed_Object<ACE_Recursive_Thread_Mutex>::get_preallocated_object
          (ACE_Object_Manager::ACE_SIG_HANDLER_LOCK);
          ACE_GUARD (ACE_Recursive_Thread_Mutex, m, *lock));
  ACE_Sig_Handler::sig_pending_ = pending;
}

cancel_thr (ACE_Thread_Descriptor *td, int async_cancel)
{
  ACE_TRACE ("ACE_Thread_Manager::cancel_thr");

  ACE_SET_BITS (td->thr_state_, ACE_THR_CANCELLED);

  if (async_cancel != 0)


    return ACE_Thread::cancel (td->thr_id_);

  return 0;
}

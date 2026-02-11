shutdown (void)
{
  ACE_TRACE ("ACE_Barrier::shutdown");
  ACE_GUARD_RETURN (ACE_Thread_Mutex, ace_mon, this->lock_, -1);

  ACE_Sub_Barrier *sbp =
    this->sub_barrier_[this->current_generation_];


  if (sbp == 0)
    {
      errno = ESHUTDOWN;
      return -1;
    }


  this->sub_barrier_[0] = 0;
  this->sub_barrier_[1] = 0;

  sbp->running_threads_ = this->count_;
  sbp->barrier_finished_.broadcast ();

  return 0;
}

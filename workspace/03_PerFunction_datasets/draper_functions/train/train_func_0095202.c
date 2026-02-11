reset_timeout (void)
{
  if (this->timeout_)
    ::Tk_DeleteTimerHandler (this->timeout_);
  timeout_ = 0;

  ACE_Time_Value *max_wait_time =
    this->timer_queue_->calculate_timeout (0);

  if (max_wait_time)
    timeout_ = ::Tk_CreateTimerHandler (max_wait_time->msec (),
                                        TimerCallbackProc,
                                        (ClientData) this);
}

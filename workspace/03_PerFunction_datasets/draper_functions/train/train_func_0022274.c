acquire_read_token (ACE_Time_Value *max_wait_time)
{
  ACE_TRACE ("ACE_TP_Token_Guard::acquire_read_token");


  int result = 0;

  if (max_wait_time)
    {
      ACE_Time_Value tv = ACE_OS::gettimeofday ();
      tv += *max_wait_time;

      ACE_MT (result = this->token_.acquire_read (&ACE_TP_Reactor::no_op_sleep_hook,
                                                  0,
                                                  &tv));
    }
  else
    {
      ACE_MT (result = this->token_.acquire_read (&ACE_TP_Reactor::no_op_sleep_hook));
    }


  if (result == -1)
    {
      if (errno == ETIME)
        return 0;
      else
        return -1;
    }


  this->owner_ = true;

  return result;
}

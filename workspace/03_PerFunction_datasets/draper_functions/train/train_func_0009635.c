notify (ACE_Event_Handler *event_handler,
                                   ACE_Reactor_Mask mask,
                                   ACE_Time_Value *timeout)
{
  ACE_TRACE ("ACE_Select_Reactor_Notify::notify");


  if (this->select_reactor_ == 0)
    return 0;

  ACE_Event_Handler_var safe_handler (event_handler);

  if (event_handler)
    {
      event_handler->add_reference ();
    }

  ACE_Notification_Buffer buffer (event_handler, mask);

#if defined (ACE_HAS_REACTOR_NOTIFICATION_QUEUE)
  int const notification_required =
    notification_queue_.push_new_notification(buffer);

  if (notification_required == -1)
    {
      return -1;
    }

  if (notification_required == 0)
    {

      safe_handler.release ();

      return 0;
    }
#endif

  ssize_t const n = ACE::send (this->notification_pipe_.write_handle (),
                               (char *) &buffer,
                               sizeof buffer,
                               timeout);
  if (n == -1)
    {
      return -1;
    }


  safe_handler.release ();

  return 0;
}

notify (ACE_Event_Handler *eh,
                                     ACE_Reactor_Mask mask,
                                     ACE_Time_Value *timeout)
{
  ACE_TRACE ("ACE_Dev_Poll_Reactor_Notify::notify");


  if (this->dp_reactor_ == 0)
    return 0;

  ACE_Notification_Buffer buffer (eh, mask);

#if defined (ACE_HAS_REACTOR_NOTIFICATION_QUEUE)
  ACE_UNUSED_ARG (timeout);
  ACE_Dev_Poll_Handler_Guard eh_guard (eh);


  if (-1 == this->notification_queue_.push_new_notification (buffer))
    return -1;


  eh_guard.release ();


  ssize_t n = ACE::send (this->notification_pipe_.write_handle (),
                         (char *) &buffer,
                         1);
  if (n == -1 && (errno != EAGAIN))
    return -1;

  return 0;
#else

  ACE_Dev_Poll_Handler_Guard eh_guard (eh);

  ssize_t n = ACE::send (this->notification_pipe_.write_handle (),
                         (char *) &buffer,
                         sizeof buffer,
                         timeout);
  if (n == -1)
    return -1;

  eh_guard.release ();

  return 0;
#endif
}

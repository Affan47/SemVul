ACE_POSIX_Asynch_Timer
  (const ACE_Handler::Proxy_Ptr &handler_proxy,
   const void *act,
   const ACE_Time_Value &tv,
   ACE_HANDLE event,
   int priority,
   int signal_number)
  : ACE_POSIX_Asynch_Result
     (handler_proxy, act, event, 0, 0, priority, signal_number),
    time_ (tv)
{
}

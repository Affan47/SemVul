ACE_POSIX_Asynch_Connect_Result
  (const ACE_Handler::Proxy_Ptr &handler_proxy,
   ACE_HANDLE connect_handle,
   const void* act,
   ACE_HANDLE event,
   int priority,
   int signal_number)
  : ACE_POSIX_Asynch_Result
      (handler_proxy, act, event, 0, 0, priority, signal_number)
{
  this->aio_fildes = connect_handle;
  this->aio_nbytes = 0;
}

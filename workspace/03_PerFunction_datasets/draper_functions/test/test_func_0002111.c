create_asynch_accept_result
  (const ACE_Handler::Proxy_Ptr &handler_proxy,
   ACE_HANDLE listen_handle,
   ACE_HANDLE accept_handle,
   ACE_Message_Block &message_block,
   size_t bytes_to_read,
   const void* act,
   ACE_HANDLE event,
   int priority,
   int signal_number)
{
  ACE_Asynch_Accept_Result_Impl *implementation;
  ACE_NEW_RETURN (implementation,
                  ACE_POSIX_Asynch_Accept_Result (handler_proxy,
                                                  listen_handle,
                                                  accept_handle,
                                                  message_block,
                                                  bytes_to_read,
                                                  act,
                                                  event,
                                                  priority,
                                                  signal_number),
                  0);
  return implementation;
}

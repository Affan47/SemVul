ACE_POSIX_Asynch_Read_Stream_Result
  (const ACE_Handler::Proxy_Ptr &handler_proxy,
   ACE_HANDLE handle,
   ACE_Message_Block &message_block,
   size_t bytes_to_read,
   const void* act,
   ACE_HANDLE event,
   int priority,
   int signal_number)
  : ACE_POSIX_Asynch_Result
      (handler_proxy, act, event, 0, 0, priority, signal_number),
    message_block_ (message_block)
{
  this->aio_fildes = handle;
  this->aio_buf = message_block.wr_ptr ();
  this->aio_nbytes = bytes_to_read;
}

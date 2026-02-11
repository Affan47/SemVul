send (const ACE_Message_Block *message_block,
                  const ACE_Time_Value *timeout)
{
  ACE_TRACE ("ACE_MEM_IO::send");

  if (this->deliver_strategy_ == 0)
    {
      return -1;
    }

  size_t len = message_block->total_length ();

  if (len != 0)
    {
      ACE_MEM_SAP_Node *buf =
        reinterpret_cast<ACE_MEM_SAP_Node *> (
          this->deliver_strategy_->acquire_buffer (
            ACE_Utils::truncate_cast<ssize_t> (len)));

      size_t n = 0;

      while (message_block != 0)
        {
          ACE_OS::memcpy (static_cast<char *> (buf->data ()) + n,
                          message_block->rd_ptr (),
                          message_block->length ());
          n += message_block->length ();

          if (message_block->cont ())
            {
              message_block = message_block->cont ();
            }
          else
            {
              message_block = message_block->next ();
            }
        }

      buf->size_ = len;

      return this->deliver_strategy_->send_buf (buf,
                                                0,
                                                timeout);
    }

  return 0;
}

do_SSL_read (void)
{
  if (this->ext_read_result_ == 0)
    {
      return 0;
    }

  if (this->flags_ & SF_REQ_SHUTDOWN)
    {
      this->notify_read (0, ERR_CANCELED);
      return -1;
    }

  ACE_Message_Block & mb = this->ext_read_result_->message_block ();
  size_t bytes_req = this->ext_read_result_->bytes_to_read ();

  ERR_clear_error ();

  const int bytes_trn =
    ::SSL_read (this->ssl_,
                mb.wr_ptr (),
                ACE_Utils::truncate_cast<int> (bytes_req));

  int const status = ::SSL_get_error (this->ssl_, bytes_trn);

  switch (status)
    {
    case SSL_ERROR_NONE:
      this->notify_read (bytes_trn, 0);
      return 1;

    case SSL_ERROR_WANT_READ:
    case SSL_ERROR_WANT_WRITE:
      return 0;

    case SSL_ERROR_ZERO_RETURN:
      this->notify_read (0, 0);
      return 1;

    case SSL_ERROR_SYSCALL:
      if (bytes_trn == 0)
        {
          this->notify_read (0, 0);
          return 1;
        }


    default:
      break;
    }

 this->notify_read (0, EFAULT);
 this->print_error (status,
                    ACE_TEXT ("SSL_read error"));

 return -1;
}

Read(void* data, size_t data_len,
                                        size_t* read, int* error) {
  LOG(LS_INFO) << "OpenSSLStreamAdapter::Read(" << data_len << ")";
  switch (state_) {
    case SSL_NONE:

      return StreamAdapterInterface::Read(data, data_len, read, error);

    case SSL_WAIT:
    case SSL_CONNECTING:
      return SR_BLOCK;

    case SSL_CONNECTED:
      break;

    case SSL_CLOSED:
      return SR_EOS;

    case SSL_ERROR:
    default:
      if (error)
        *error = ssl_error_code_;
      return SR_ERROR;
  }


  if (data_len == 0) {
    if (read)
      *read = 0;
    return SR_SUCCESS;
  }

  ssl_read_needs_write_ = false;

  int code = SSL_read(ssl_, data, data_len);
  int ssl_error = SSL_get_error(ssl_, code);
  switch (ssl_error) {
    case SSL_ERROR_NONE:
      LOG(LS_INFO) << " -- success";
      ASSERT(0 < code && static_cast<unsigned>(code) <= data_len);
      if (read)
        *read = code;

      if (ssl_mode_ == SSL_MODE_DTLS) {

        unsigned int pending = SSL_pending(ssl_);

        if (pending) {
          LOG(LS_INFO) << " -- short DTLS read. flushing";
          FlushInput(pending);
          if (error)
            *error = SSE_MSG_TRUNC;
          return SR_ERROR;
        }
      }
      return SR_SUCCESS;
    case SSL_ERROR_WANT_READ:
      LOG(LS_INFO) << " -- error want read";
      return SR_BLOCK;
    case SSL_ERROR_WANT_WRITE:
      LOG(LS_INFO) << " -- error want write";
      ssl_read_needs_write_ = true;
      return SR_BLOCK;
    case SSL_ERROR_ZERO_RETURN:
      LOG(LS_INFO) << " -- remote side closed";
      return SR_EOS;
      break;
    default:
      LOG(LS_INFO) << " -- error " << code;
      Error("SSL_read", (ssl_error ? ssl_error : -1), false);
      if (error)
        *error = ssl_error_code_;
      return SR_ERROR;
  }

}

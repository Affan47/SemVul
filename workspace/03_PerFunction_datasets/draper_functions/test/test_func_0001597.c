CloseStderr(void) {
    if (stderr_ != -1) ::close(stderr_);
    stderr_ = -1;
    SAFE_DISCONNECT(stderr_conn_);
  }

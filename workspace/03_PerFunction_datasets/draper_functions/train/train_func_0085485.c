ap_set_timeout(FXInputHandle handle,FXint timeout) {
  struct timeval tv;

  memset(&tv,0,sizeof(struct timeval));

  tv.tv_sec  = timeout;


  if (setsockopt(handle,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(struct timeval)))
    return false;


  if (setsockopt(handle,SOL_SOCKET,SO_SNDTIMEO,&tv,sizeof(struct timeval)))
    return false;

  return true;
  }

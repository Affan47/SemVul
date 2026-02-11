setStreamCallback(RtAudioCallback callback, void *userData)
{
  verifyStream();

  CallbackInfo *info = (CallbackInfo *) &stream_.callbackInfo;
  if ( info->usingCallback ) {
    sprintf(message_, "RtApiOss: A callback is already set for this stream!");
    error(RtError::WARNING);
    return;
  }

  info->callback = (void *) callback;
  info->userData = userData;
  info->usingCallback = true;
  info->object = (void *) this;


  pthread_attr_t attr;
  pthread_attr_init(&attr);


  int err = pthread_create(&(info->thread), &attr, ossCallbackHandler, &stream_.callbackInfo);
  pthread_attr_destroy(&attr);
  if (err) {
    info->usingCallback = false;
    sprintf(message_, "RtApiOss: error starting callback thread!");
    error(RtError::THREAD_ERROR);
  }
}

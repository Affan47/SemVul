ossCallbackHandler(void *ptr)
{
  CallbackInfo *info = (CallbackInfo *) ptr;
  RtApiOss *object = (RtApiOss *) info->object;
  bool *usingCallback = &info->usingCallback;

  while ( *usingCallback ) {
    pthread_testcancel();
    try {
      object->tickStream();
    }
    catch (RtError &exception) {
      EM_log( CK_LOG_SYSTEM, "RtApiOss: callback thread error..." );
      EM_pushlog();
      EM_log( CK_LOG_INFO, "(%s)", exception.getMessageString() );
      EM_log( CK_LOG_INFO, "closing thread..." );
      EM_poplog();
      break;
    }
  }

  return 0;
}

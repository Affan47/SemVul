_pthread_kill(pthread_t th,int sig) {
  int ret=ESRCH;
  _pthread_descr td;
  if (th==getpid()) {
    ret=(kill(th,sig)==-1)?_errno_:0;
  }
  else {
    _pthread_descr this=__thread_self();
    __NO_ASYNC_CANCEL_BEGIN_(this);
    if ((td=__thread_find(th))) {
      UNLOCK(td);
      ret=(kill(th,sig)==-1)?_errno_:0;
    }
    __NO_ASYNC_CANCEL_END_(this);
  }
  return ret;
}

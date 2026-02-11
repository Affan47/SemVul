signal_management_thread(void *PTR)
{
  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, 0);
  sigset_t blocked;
  sigprocmask(SIG_SETMASK, 0, &blocked);
  int s;
  sigwait(&blocked, &s);
  if(s != SIGSEGV) {
    sigprocmask(SIG_UNBLOCK, &blocked, 0);
  }
  signal_management_handler(s);
  return NULL;
}

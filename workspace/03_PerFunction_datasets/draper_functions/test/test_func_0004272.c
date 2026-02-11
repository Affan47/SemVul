__thread_setcanceltype(int type,int*oldtype,_pthread_descr td) {
  if ((type!=PTHREAD_CANCEL_DEFERRED)&&(type!=PTHREAD_CANCEL_ASYNCHRONOUS)) return EINVAL;
  if (oldtype) *oldtype=td->canceltype;
  td->canceltype=type;
  return 0;
}

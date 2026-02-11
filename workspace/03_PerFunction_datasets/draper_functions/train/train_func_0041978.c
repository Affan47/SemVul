__MGR_send(void(*f)(void*),void*arg) {
  __thread_manager_func data={ .func=f, .arg=arg, };
  __pthread_once(&__thread_started,__thread_init);
  return INTR_RETRY(__libc_write(mgr_send_fd,&data,sizeof(data)));
}

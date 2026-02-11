__thread_start_new(_thread_descr data) {
  int pid;

  data->pid=&pid;

  if (__MGR_send((MGR_func)__MGR_thread_start_new,data)==-1) {
    __thread_cleanup(data->tr);
    return -1;
  }
  __thread_suspend(data->tr,0);
  return pid;
}

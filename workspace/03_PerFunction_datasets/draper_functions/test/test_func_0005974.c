mtcp_get_thread_from_freelist()
{
  Thread *thread;

  lock_threads ();
  if (threads_freelist == NULL) {
    thread = (Thread*) mtcp_safe_malloc(sizeof(Thread));
    if (thread == NULL) {
      MTCP_PRINTF("Error allocating thread struct\n");
      mtcp_abort();
    }
  } else {
    thread = threads_freelist;
    threads_freelist = threads_freelist->next;
  }
  unlk_threads ();
  memset(thread, 0, sizeof (*thread));
  return thread;
}

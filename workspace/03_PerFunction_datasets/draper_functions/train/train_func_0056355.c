mtcp_process_pthread_join (pthread_t pth)
{
  struct Thread *thread;
  for (thread = threads; thread != NULL; thread = thread -> next) {
    if (pthread_equal(thread -> pth, pth)) {
      lock_threads();
      threadisdead(thread);
      unlk_threads();
      break;
    }
  }
}

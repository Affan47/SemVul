bnet_stop_thread_server(pthread_t tid)
{
   quit = true;
   if (!pthread_equal(tid, pthread_self())) {
      pthread_kill(tid, TIMEOUT_SIGNAL);
   }
}

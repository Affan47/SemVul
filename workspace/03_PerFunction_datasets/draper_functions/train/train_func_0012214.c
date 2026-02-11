signal_emitter(void* anArg)
{
   int sig[3] = {SIGPIPE, SIGUSR1, SIGUSR2};
   unsigned int i = (unsigned int)pthread_self();
   bool done = false;

   while (!done) {
      int j = (rand_r(&i) % 3);

      if (should_quit() == TRUE) {
         printf("signal_emitter: will terminate\n");
         done = true;
         break;
      }

      printf("signal_emitter %d will raise: %d\n", (int)pthread_self(), sig[j]);
      kill(getpid(), sig[j]);
      sleep(4);
   }

   return NULL;
}

smp_wakeup(void) {

   int id;

   ThreadNb = option_get_int("Threads");

   for (id = 1; id < ThreadNb; id++) {

      ASSERT(Thread[id].stage==STAGE_SLEEP);

      Thread[id].split_nb = 0;
      Thread[id].split_used = NULL;

#ifdef _MSC_VER
      SetEvent(Thread[id].wait);
#else
      pthread_cond_broadcast(&Thread[id].wait);
#endif

      while(Thread[id].stage==STAGE_SLEEP);
   }


   Thread[ThreadMain].stage = STAGE_SEARCH;
   Thread[ThreadMain].split_nb = 0;
   Thread[ThreadMain].split_used = NULL;
}

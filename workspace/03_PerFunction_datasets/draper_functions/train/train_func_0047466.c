KillESIThreads (void)
{
   int i;
   printf ("Disabling ALL ESI reponses.\n");
   for (i = 0; i < MAX_ESI_ENTRIES; i++)
   {
      if (esi_tble[i].t_hdle != 0)
      {
#ifdef SNS_LINUX
         pthread_cancel(*(esi_tble[i].t_hdle));
         free(esi_tble[i].t_hdle);
         esi_tble[i].t_hdle = 0;
#else
         TerminateThread (esi_tble[i].t_hdle, -1);
#endif
      }
   }
}

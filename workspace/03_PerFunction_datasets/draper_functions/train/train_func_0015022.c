_e_main_cb_idle_after(void *data __UNUSED__)
{
   static int first_idle;

   edje_freeze();

#ifdef E17_RELEASE_BUILD
   first_idle = 1;
   if (first_idle)
     {
        TS("SLEEP");
        first_idle = 0;
        e_precache_end = EINA_TRUE;
     }
#else
   if (first_idle++ < 60)
     {
        TS("SLEEP");
        if (!first_idle)
          e_precache_end = EINA_TRUE;
     }
#endif

   return ECORE_CALLBACK_RENEW;
}

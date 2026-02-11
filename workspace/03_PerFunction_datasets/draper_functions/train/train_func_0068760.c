initiate_hibernate(UPSINFO *ups)
{
   FILE *pwdf;
   int killcount;

   if (ups->mode.type == DUMB_UPS) {

      for (killcount = 0; killcount < 3; killcount++)
         device_read_volatile_data(ups);
   }


   pwdf = fopen(ups->pwrfailpath, "r");
   if ((pwdf == NULL && ups->mode.type != DUMB_UPS) ||
       (pwdf == NULL && ups->is_onbatt() && ups->mode.type == DUMB_UPS)) {


      log_event(ups, LOG_WARNING,
         "Cannot find %s file.\n Killpower requested in "
           "non-power fail condition or bug.\n Killpower request "
           "ignored at %s:%d\n", ups->pwrfailpath, __FILE__, __LINE__);
      Error_abort3(
         "Cannot find %s file.\n Killpower requested in "
           "non-power fail condition or bug.\n Killpower request "
           "ignored at %s:%d\n", ups->pwrfailpath, __FILE__, __LINE__);
   } else {

      if (ups->upsclass.type == SHAREMASTER) {
         log_event(ups, LOG_WARNING,
            "Waiting 30 seconds for slave(s) to shutdown.");
         sleep(30);
      }


      if (pwdf)
         fclose(pwdf);

      log_event(ups, LOG_WARNING, "Attempting to kill the UPS power!");

      if (ups->upsclass.type == SHARESLAVE) {
         sleep(10);
         log_event(ups, LOG_WARNING, "Waiting For ShareUPS Master to shutdown");
         sleep(60);
         log_event(ups, LOG_WARNING, "Failed to have power killed by Master!");


         log_event(ups, LOG_WARNING, "Perform CPU-reset or power-off");
         return;
      } else {

         device_kill_power(ups);
      }
   }
}

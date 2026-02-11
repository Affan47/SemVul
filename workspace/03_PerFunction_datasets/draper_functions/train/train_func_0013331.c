UPSlinkCheck(UPSINFO *ups)
{
   struct timeval now, prev, start;
   static int linkcheck = FALSE;

   if (linkcheck)
      return;

   linkcheck = TRUE;

   tcflush(ups->fd, TCIOFLUSH);
   if (strcmp(smart_poll('Y', ups), "SM") == 0) {
      linkcheck = FALSE;
      ups->clear_commlost();
      return;
   }

   write_unlock(ups);

   gettimeofday(&start, NULL);
   prev = start;

   tcflush(ups->fd, TCIOFLUSH);
   while (strcmp(smart_poll('Y', ups), "SM") != 0) {

      gettimeofday(&now, NULL);
      if (TV_DIFF_MS(start, now) >= COMMLOST_TIMEOUT_MS) {

         if (!ups->is_commlost()) {
            ups->set_commlost();
            generate_event(ups, CMDCOMMFAILURE);
            prev = now;
         }


         if (TV_DIFF_MS(prev, now) >= 10*60*1000) {
            log_event(ups, event_msg[CMDCOMMFAILURE].level,
               event_msg[CMDCOMMFAILURE].msg);
            prev = now;
         }
      }


      sleep(1);
      tcflush(ups->fd, TCIOFLUSH);
   }

   write_lock(ups);

   if (ups->is_commlost()) {
      ups->clear_commlost();
      generate_event(ups, CMDCOMMOK);
   }

   linkcheck = FALSE;
}

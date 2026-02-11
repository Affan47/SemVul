is_watchdog()
{
   if (wd_is_init && pthread_equal(pthread_self(), wd_tid)) {
      return true;
   } else {
      return false;
   }
}

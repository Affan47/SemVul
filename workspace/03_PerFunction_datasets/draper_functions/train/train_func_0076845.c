mplayer_sigchld()
{
   static time_t  last_sigchld = -1;

   if (kill(mplayer_state.pid, 0) != 0) {
      if (time(0) - last_sigchld <= 1) {
         if (mplayer_callback_fatal != NULL)
            mplayer_sigchld_message();
      } else {
         mplayer_restart();
         if (mplayer_callback_error != NULL)
            mplayer_callback_error("%s died.  Restarting it.", MPLAYER_PATH);
      }
   }

   last_sigchld = time(0);
}

mplayer_volume_step(float percent)
{
   static const char *cmd_fmt = "\npausing_keep volume %f\n";
   char *cmd;

   if (!mplayer_state.playing)
      return;


   if (mplayer_state.volume > -1) {
      percent += mplayer_state.volume;
      mplayer_volume_set(percent);
      return;
   }

   if (asprintf(&cmd, cmd_fmt, percent) == -1)
      err(1, "%s: asprintf failed", __FUNCTION__);

   mplayer_send_cmd(cmd);
   free(cmd);

   mplayer_volume_query();
}

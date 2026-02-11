mplayer_volume_set(float percent)
{
   static const char *cmd_fmt = "\npausing_keep set_property volume %f\n";
   char *cmd;

   if (!mplayer_state.playing)
      return;

   if (percent > 100) percent = 100;
   if (percent < 0)   percent = 0;

   if (asprintf(&cmd, cmd_fmt, percent) == -1)
      err(1, "%s: asprintf failed", __FUNCTION__);


   mplayer_send_cmd(cmd);
   free(cmd);

   mplayer_volume_query();
}

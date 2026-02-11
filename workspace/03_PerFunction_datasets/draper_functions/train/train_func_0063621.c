do_demo (saver_screen_info *ssi)
{
  saver_info *si = ssi->global;
  saver_preferences *p = &si->prefs;
  const char *cmd = p->demo_command;

  if (cmd && *cmd)
    fork_and_exec (ssi, cmd);
  else
    fprintf (stderr, "%s: no demo-mode command has been specified.\n",
             blurb());
}

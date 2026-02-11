toggle_forcesig (void)
{
  struct agent_card_info_s info;
  int rc;
  int newstate;

  memset (&info, 0, sizeof info);
  rc = agent_scd_getattr ("CHV-STATUS", &info);
  if (rc)
    {
      log_error ("error getting current status: %s\n", gpg_strerror (rc));
      return;
    }
  newstate = !info.chv1_cached;
  agent_release_card_info (&info);

  rc = agent_scd_setattr ("CHV-STATUS-1", newstate? "\x01":"", 1, NULL);
  if (rc)
    log_error ("error toggling signature PIN flag: %s\n", gpg_strerror (rc));
  write_sc_op_status (rc);
}

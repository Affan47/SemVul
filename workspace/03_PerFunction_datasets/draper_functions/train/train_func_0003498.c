xsmp_interact (SmcConn   smc_conn,
	       SmPointer client_data)
{
  EggSMClientXSMP *xsmp = client_data;
  EggSMClient *client = client_data;

  g_debug ("Received Interact message in state %s",
	   EGG_SM_CLIENT_XSMP_STATE (xsmp));

  if (xsmp->state != XSMP_STATE_INTERACT_REQUEST)
    {
      fix_broken_state (xsmp, "Interact", TRUE, TRUE);
      return;
    }

  xsmp->state = XSMP_STATE_INTERACT;
  egg_sm_client_quit_requested (client);
}

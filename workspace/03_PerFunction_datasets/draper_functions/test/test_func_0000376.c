xsmp_save_complete (SmcConn   smc_conn,
		    SmPointer client_data)
{
  EggSMClientXSMP *xsmp = client_data;

  g_debug ("Received SaveComplete message in state %s",
	   EGG_SM_CLIENT_XSMP_STATE (xsmp));

  if (xsmp->state == XSMP_STATE_SAVE_YOURSELF_DONE)
    xsmp->state = XSMP_STATE_IDLE;
  else
    fix_broken_state (xsmp, "SaveComplete", FALSE, FALSE);
}

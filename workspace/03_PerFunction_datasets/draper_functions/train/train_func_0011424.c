kill_script(int k)
{
  if (rinfo[k] != NULL)
    {
      int i;

      kill_callbacks_owned_by_script(k);


      for (i = 1; i < MAX_VARS; i++)
	{
	  if (play.var[i].active && play.var[i].scope == k)
	    play.var[i].active = 0;
	}
      log_debug("Killed script %s. (num %d)", rinfo[k]->name, k);

      if (rinfo[k]->name != NULL)
	free(rinfo[k]->name);
      if (rinfo[k] != NULL)
	free(rinfo[k]);
      rinfo[k] = NULL;
      if (rbuf[k] != NULL)
	free(rbuf[k]);
      rbuf[k] = NULL;
    }
}

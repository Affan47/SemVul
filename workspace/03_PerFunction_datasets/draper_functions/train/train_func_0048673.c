free_register_move_costs (void)
{
  int mode, i;


  for (mode = 0; mode < MAX_MACHINE_MODE; mode++)
    if (ira_register_move_cost[mode])
      {
	for (i = 0;
	     i < mode && (ira_register_move_cost[i]
			  != ira_register_move_cost[mode]);
	     i++)
	  ;
	if (i == mode)
	  {
	    free (ira_register_move_cost[mode]);
	    free (ira_may_move_in_cost[mode]);
	    free (ira_may_move_out_cost[mode]);
	  }
      }
  memset (ira_register_move_cost, 0, sizeof ira_register_move_cost);
  memset (ira_may_move_in_cost, 0, sizeof ira_may_move_in_cost);
  memset (ira_may_move_out_cost, 0, sizeof ira_may_move_out_cost);
  last_mode_for_init_move_cost = -1;
}

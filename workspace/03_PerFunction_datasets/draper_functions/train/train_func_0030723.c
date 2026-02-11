borg_flow_vault(int nearness)
{
    int y,x,i;
	int b_y, b_x;

	borg_grid *ag;


    borg_temp_n = 0;
    i=0;


	if (!vault_on_level) return (FALSE);


    for (y = w_y; y < w_y + SCREEN_HGT; y++)
    {
        for (x = w_x; x < w_x + SCREEN_WID; x++)
		{


			if (distance(c_y, c_x, y, x) > nearness) continue;


			if (borg_grids[y][x].feat < FEAT_MAGMA ||
				borg_grids[y][x].feat > FEAT_PERM_EXTRA) continue;


			for (i=0; i < 8; i++)
			{
	           	b_x = x + ddx_ddd[i];
	           	b_y = y + ddy_ddd[i];


	            if (!in_bounds_fully(b_y, b_x)) continue;


	           	ag = &borg_grids[b_y][b_x];


				if (ag->feat != FEAT_PERM_INNER) continue;


				borg_temp_y[borg_temp_n] = y;
				borg_temp_x[borg_temp_n] = x;
				borg_temp_n++;
			}

        }
     }


    if (!borg_temp_n) return (FALSE);


    for (i = 0; i < borg_temp_n; i++)
    {

        borg_flow_enqueue_grid(borg_temp_y[i], borg_temp_x[i]);
    }


    borg_flow_spread(250, TRUE, FALSE, FALSE, -1, FALSE);


    if (!borg_flow_commit("vault excavation", GOAL_VAULT)) return (FALSE);


    if (!borg_flow_old(GOAL_VAULT)) return (FALSE);


    return (TRUE);
}

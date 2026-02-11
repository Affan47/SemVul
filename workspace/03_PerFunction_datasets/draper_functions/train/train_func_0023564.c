borg_flow_stair_less(int why, bool sneak)
{
    int i;


    if (!track_less_num) return (FALSE);


    borg_flow_clear();


    borg_needs_searching = FALSE;


    for (i = 0; i < track_less_num; i++)
    {

		if (borg_grids[track_less_y[i]][track_less_x[i]].kill) continue;


        borg_flow_enqueue_grid(track_less_y[i], track_less_x[i]);
    }

    if (borg_skill[BI_CLEVEL] > 35 || borg_skill[BI_CURLITE] == 0)
    {

        borg_flow_spread(250, TRUE, FALSE, FALSE, -1, sneak);
    }
    else
    {

        borg_flow_spread(250, FALSE, !borg_desperate, FALSE, -1, sneak);
    }


    if (!borg_flow_commit("up-stairs", why)) return (FALSE);


    if (!borg_flow_old(why)) return (FALSE);


    return (TRUE);
}

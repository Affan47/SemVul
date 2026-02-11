borg_surrounded(void)
{
    borg_kill *kill;
    monster_race *r_ptr;

    int safe_grids = 8;
    int non_safe_grids = 0;
    int monsters = 0;
    int adjacent_monsters = 0;

    int x9, y9, ax, ay, d;
    int i;


    for (i = 1; i < borg_kills_nxt; i++)
    {
        kill = &borg_kills[i];
        r_ptr = &r_info[kill->r_idx];


        if (!kill->r_idx) continue;

        x9 = kill->x;
        y9 = kill->y;


        ax = (x9 > c_x) ? (x9 - c_x) : (c_x - x9);
        ay = (y9 > c_y) ? (y9 - c_y) : (c_y - y9);


        d = MAX(ax, ay);


        if (d > 3) continue;


        if (!borg_los(c_y, c_x, y9, x9)) continue;


        if (!kill->awake) continue;


		if (rf_has(r_ptr->flags, RF_PASS_WALL)) continue;
		if (rf_has(r_ptr->flags, RF_KILL_WALL)) continue;


        if (d == 1) adjacent_monsters ++;


        monsters ++;

    }


    for (i = 0; i < 8; i++)
    {
        int x = c_x + ddx_ddd[i];
        int y = c_y + ddy_ddd[i];


        borg_grid *ag = &borg_grids[y][x];


		if (!in_bounds_fully(y,x)) continue;


        if (!borg_cave_floor_grid(ag)) non_safe_grids ++;


        else if (ag->feat == FEAT_NONE) non_safe_grids ++;


        else if (ag->kill) non_safe_grids ++;


        else if ((ag->feat >= FEAT_SHOP_HEAD) && (ag->feat <= FEAT_SHOP_TAIL)) non_safe_grids ++;


        if ((ag->feat >= FEAT_TRAP_HEAD) && (ag->feat <= FEAT_TRAP_TAIL)) non_safe_grids ++;

    }


    safe_grids = safe_grids - non_safe_grids;


    if (safe_grids == 1 && adjacent_monsters == 1) return (FALSE);


    if (monsters > safe_grids)
    {
        borg_note(format("# Possibility of being surrounded (monsters/safegrids)(%d/%d)",
        monsters, safe_grids));


        if (goal_ignoring)
		{


		}
        else return (TRUE);
    }


    return (FALSE);
}

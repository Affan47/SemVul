borg_flow_dark_reachable(int y, int x)
{
    int j;

    borg_grid *ag;


    for (j = 0; j < 8; j++)
    {
        int y2 = y + ddy_ddd[j];
        int x2 = x + ddx_ddd[j];


        ag = &borg_grids[y2][x2];


        if (ag->feat == FEAT_NONE) continue;


        if (borg_cave_floor_grid(ag)) return (TRUE);
    }


    return (FALSE);
}

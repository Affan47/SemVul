A_PotteryCheck(mobj_t * actor)
{
    int i;
    mobj_t *pmo;

    if (!netgame)
    {
        pmo = players[consoleplayer].mo;
        if (P_CheckSight(actor, pmo) && (abs(R_PointToAngle2(pmo->x,
                                                             pmo->y, actor->x,
                                                             actor->y) -
                                             pmo->angle) <= ANG45))
        {
            P_SetMobjState(actor, actor->state - &states[0] - 1);
        }
        else
        {
            return;
        }
    }
    else
    {
        for (i = 0; i < MAXPLAYERS; i++)
        {
            if (!playeringame[i])
            {
                continue;
            }
            pmo = players[i].mo;
            if (P_CheckSight(actor, pmo) && (abs(R_PointToAngle2(pmo->x,
                                                                 pmo->y,
                                                                 actor->x,
                                                                 actor->y) -
                                                 pmo->angle) <= ANG45))
            {
                P_SetMobjState(actor, actor->state - &states[0] - 1);
                return;
            }
        }
    }
}

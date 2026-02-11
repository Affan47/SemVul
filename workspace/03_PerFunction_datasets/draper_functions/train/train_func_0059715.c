A_MaceBallImpact(mobj_t * ball)
{
    if ((ball->z <= ball->floorz) && (P_HitFloor(ball) != FLOOR_SOLID))
    {
        P_RemoveMobj(ball);
        return;
    }
    if ((ball->health != MAGIC_JUNK) && (ball->z <= ball->floorz)
        && ball->momz)
    {
        ball->health = MAGIC_JUNK;
        ball->momz = (ball->momz * 192) >> 8;
        ball->flags2 &= ~MF2_FLOORBOUNCE;
        P_SetMobjState(ball, ball->info->spawnstate);
        S_StartSound(ball, sfx_bounce);
    }
    else
    {
        ball->flags |= MF_NOGRAVITY;
        ball->flags2 &= ~MF2_LOGRAV;
        S_StartSound(ball, sfx_lobhit);
    }
}

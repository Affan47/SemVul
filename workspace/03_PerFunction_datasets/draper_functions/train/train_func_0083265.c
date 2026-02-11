A_VolcBallImpact(mobj_t * ball)
{
    int i;
    mobj_t *tiny;
    angle_t angle;

    if (ball->z <= ball->floorz)
    {
        ball->flags |= MF_NOGRAVITY;
        ball->flags2 &= ~MF2_LOGRAV;
        ball->z += 28 * FRACUNIT;

    }
    P_RadiusAttack(ball, ball->target, 25);
    for (i = 0; i < 4; i++)
    {
        tiny = P_SpawnMobj(ball->x, ball->y, ball->z, MT_VOLCANOTBLAST);
        tiny->target = ball;
        angle = i * ANG90;
        tiny->angle = angle;
        angle >>= ANGLETOFINESHIFT;
        tiny->momx = FixedMul((fixed_t)(FRACUNIT * .7), finecosine[angle]);
        tiny->momy = FixedMul((fixed_t)(FRACUNIT * .7), finesine[angle]);
        tiny->momz = FRACUNIT + (P_Random() << 9);
        P_CheckMissileSpawn(tiny);
    }
}

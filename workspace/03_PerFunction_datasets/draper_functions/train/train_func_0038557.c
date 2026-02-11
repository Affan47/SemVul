A_WraithFX2(mobj_t * actor)
{
    mobj_t *mo;
    angle_t angle;
    int i;

    for (i = 0; i < 2; i++)
    {
        mo = P_SpawnMobj(actor->x, actor->y, actor->z, MT_WRAITHFX2);
        if (mo)
        {
            if (P_Random() < 128)
            {
                angle = actor->angle + (P_Random() << 22);
            }
            else
            {
                angle = actor->angle - (P_Random() << 22);
            }
            mo->momz = 0;
            mo->momx = FixedMul((P_Random() << 7) + FRACUNIT,
                                finecosine[angle >> ANGLETOFINESHIFT]);
            mo->momy = FixedMul((P_Random() << 7) + FRACUNIT,
                                finesine[angle >> ANGLETOFINESHIFT]);
            mo->target = actor;
            mo->floorclip = 10 * FRACUNIT;
        }
    }
}

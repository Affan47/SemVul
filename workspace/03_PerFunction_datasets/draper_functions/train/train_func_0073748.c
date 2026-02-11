A_FireMacePL1(player_t * player, pspdef_t * psp)
{
    mobj_t *ball;

    if (P_Random() < 28)
    {
        A_FireMacePL1B(player, psp);
        return;
    }
    if (player->ammo[am_mace] < USE_MACE_AMMO_1)
    {
        return;
    }
    player->ammo[am_mace] -= USE_MACE_AMMO_1;
    psp->sx = ((P_Random() & 3) - 2) * FRACUNIT;
    psp->sy = WEAPONTOP + (P_Random() & 3) * FRACUNIT;
    ball = P_SPMAngle(player->mo, MT_MACEFX1, player->mo->angle
                      + (((P_Random() & 7) - 4) << 24));
    if (ball)
    {
        ball->special1.i = 16;
    }
}

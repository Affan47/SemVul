A_CStaffCheckBlink(player_t * player, pspdef_t * psp)
{
    if (!--player->mo->special1.i)
    {
        P_SetPsprite(player, ps_weapon, S_CSTAFFBLINK1);
        player->mo->special1.i = (P_Random() + 50) >> 2;
    }
}

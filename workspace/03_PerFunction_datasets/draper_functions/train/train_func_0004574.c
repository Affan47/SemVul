P_BringUpWeapon (player_t* player)
{
    statenum_t  newstate;

    if (player->pendingweapon == wp_nochange)
        player->pendingweapon = player->readyweapon;

    if (player->pendingweapon == wp_flame)
        S_StartSound (player->mo, sfx_flidl);

    newstate = weaponinfo[player->pendingweapon].upstate;

    player->psprites[ps_weapon].sy = WEAPONBOTTOM;
    P_SetPsprite (player, ps_weapon, newstate);


    if(player->pendingweapon == wp_elecbow)
        P_SetPsprite(player, ps_flash, S_XBOW_10);
    else if(player->pendingweapon == wp_sigil && player->sigiltype)
        P_SetPsprite(player, ps_flash, S_SIGH_00 + player->sigiltype);
    else
        P_SetPsprite(player, ps_flash, S_NULL);

    player->pendingweapon = wp_nochange;
}

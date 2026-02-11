P_CheckMana(player_t * player)
{
    manatype_t mana;
    int count;

    mana = WeaponInfo[player->readyweapon][player->class].mana;
    count = WeaponManaUse[player->class][player->readyweapon];
    if (mana == MANA_BOTH)
    {
        if (player->mana[MANA_1] >= count && player->mana[MANA_2] >= count)
        {
            return true;
        }
    }
    else if (mana == MANA_NONE || player->mana[mana] >= count)
    {
        return (true);
    }

    do
    {
        if (player->weaponowned[WP_THIRD]
            && player->mana[MANA_2] >= WeaponManaUse[player->class][WP_THIRD])
        {
            player->pendingweapon = WP_THIRD;
        }
        else if (player->weaponowned[WP_SECOND]
                 && player->mana[MANA_1] >=
                 WeaponManaUse[player->class][WP_SECOND])
        {
            player->pendingweapon = WP_SECOND;
        }
        else if (player->weaponowned[WP_FOURTH]
                 && player->mana[MANA_1] >=
                 WeaponManaUse[player->class][WP_FOURTH]
                 && player->mana[MANA_2] >=
                 WeaponManaUse[player->class][WP_FOURTH])
        {
            player->pendingweapon = WP_FOURTH;
        }
        else
        {
            player->pendingweapon = WP_FIRST;
        }
    }
    while (player->pendingweapon == WP_NOCHANGE);
    P_SetPsprite(player, ps_weapon,
                 WeaponInfo[player->readyweapon][player->class].downstate);
    return (false);
}

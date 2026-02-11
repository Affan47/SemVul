CheatHealthFunc(player_t * player, Cheat_t * cheat)
{
    if (player->morphTics)
    {
        player->health = player->mo->health = MAXMORPHHEALTH;
    }
    else
    {
        player->health = player->mo->health = MAXHEALTH;
    }
    P_SetMessage(player, TXT_CHEATHEALTH, true);
}

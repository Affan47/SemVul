P_PoisonPlayer(player_t * player, mobj_t * poisoner, int poison)
{
    if ((player->cheats & CF_GODMODE) || player->powers[pw_invulnerability])
    {
        return;
    }
    player->poisoncount += poison;
    player->poisoner = poisoner;
    if (player->poisoncount > 100)
    {
        player->poisoncount = 100;
    }
}

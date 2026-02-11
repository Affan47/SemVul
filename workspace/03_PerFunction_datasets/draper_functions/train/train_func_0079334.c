P_GiveBody(player_t * player, int num)
{
    int max;

    max = MAXHEALTH;
    if (player->chickenTics)
    {
        max = MAXCHICKENHEALTH;
    }
    if (player->health >= max)
    {
        return (false);
    }
    player->health += num;
    if (player->health > max)
    {
        player->health = max;
    }
    player->mo->health = player->health;
    return (true);
}

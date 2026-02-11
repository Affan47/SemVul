P_GiveBody(player_t* player, int num)
{
    int maxhealth;
    int healing;

    maxhealth = MAXHEALTH + player->stamina;

    if(num >= 0)
    {
        mobj_t *mo;


        if(player->health >= maxhealth)
            return false;


        player->health += num;
        if(player->health >= maxhealth)
            player->health = maxhealth;


        mo = P_SubstNullMobj(player->mo);
        mo->health = player->health;
    }
    else
    {


        healing = (-num * maxhealth) / MAXHEALTH;


        if(player->health >= healing)
            return false;


        player->health = healing;
    }

    return true;
}

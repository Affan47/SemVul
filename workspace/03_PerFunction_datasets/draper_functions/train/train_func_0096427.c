P_GiveInventoryItem(player_t *player, int sprnum, mobjtype_t type)
{
    int curinv = 0;
    int i;
    boolean ok = false;
    mobjtype_t item = 0;
    inventory_t* invtail;


    player->st_update = true;

    while(1)
    {

        if(curinv > player->numinventory)
            return true;

        item = player->inventory[curinv].type;
        if(type < item)
        {
            if(curinv != MAXINVENTORYSLOTS)
            {

                invtail = &player->inventory[player->numinventory - 1];
                if(player->numinventory >= (curinv + 1))
                {
                    for(i = player->numinventory; i >= (curinv + 1); --i)
                    {
                        invtail[1].sprite   = invtail[0].sprite;
                        invtail[1].type     = invtail[0].type;
                        invtail[1].amount   = invtail[0].amount;

                        invtail--;
                    }
                }


                player->inventory[curinv].amount = 1;
                player->inventory[curinv].sprite = sprnum;
                player->inventory[curinv].type = type;


                if(player->numinventory)
                {
                    if(curinv <= player->inventorycursor)
                        player->inventorycursor++;
                }

                player->numinventory++;

                return true;
            }

            return false;
        }

        if(type == item)
            break;

        curinv++;
    }


    if(player->inventory[curinv].amount < mobjinfo[item].mass)
    {
        player->inventory[curinv].amount++;
        ok = true;
    }
    else
        ok = false;

    return ok;
}

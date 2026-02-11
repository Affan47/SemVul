P_GiveArtifact(player_t * player, artitype_t arti, mobj_t * mo)
{
    int i;

    i = 0;
    while (player->inventory[i].type != arti && i < player->inventorySlotNum)
    {
        i++;
    }
    if (i == player->inventorySlotNum)
    {
        player->inventory[i].count = 1;
        player->inventory[i].type = arti;
        player->inventorySlotNum++;
    }
    else
    {
        if (player->inventory[i].count >= 16)
        {
            return (false);
        }
        player->inventory[i].count++;
    }
    if (player->artifactCount == 0)
    {
        player->readyArtifact = arti;
    }
    player->artifactCount++;
    if (mo && (mo->flags & MF_COUNTITEM))
    {
        player->itemcount++;
    }
    return (true);
}

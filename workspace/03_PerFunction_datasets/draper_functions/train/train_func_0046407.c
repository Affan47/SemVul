UpdatePlayerOutOfRange(Player* pPlayer)
{
    if (!pPlayer || !pPlayer->IsInWorld())
        return;

    if (pPlayer->GetGroupUpdateFlag() == GROUP_UPDATE_FLAG_NONE)
        return;

    WorldPacket data;
    pPlayer->GetSession()->BuildPartyMemberStatsChangedPacket(pPlayer, &data);

    for (GroupReference* itr = GetFirstMember(); itr != NULL; itr = itr->next())
        if (Player* player = itr->getSource())
            if (player != pPlayer && !player->HaveAtClient(pPlayer))
                player->GetSession()->SendPacket(&data);
}

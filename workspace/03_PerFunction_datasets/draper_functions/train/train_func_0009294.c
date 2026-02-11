SendUpdate()
{
    for (member_citerator citr = m_memberSlots.begin(); citr != m_memberSlots.end(); ++citr)
    {
        Player* player = sObjectMgr.GetPlayer(citr->guid);
        if (!player || !player->GetSession() || player->GetGroup() != this)
            continue;

        WorldPacket data(SMSG_GROUP_LIST, (1 + 1 + 1 + 1 + 8 + 4 + GetMembersCount() * 20));
        data << uint8(m_groupType);
        data << uint8(citr->group);
        data << uint8(GetFlags(*citr));
        data << uint8(isBGGroup() ? 1 : 0);
        if (m_groupType & GROUPTYPE_LFD)
        {
            data << uint8(0);
            data << uint32(0);
        }
        data << GetObjectGuid();
        data << uint32(0);
        data << uint32(GetMembersCount() - 1);
        for (member_citerator citr2 = m_memberSlots.begin(); citr2 != m_memberSlots.end(); ++citr2)
        {
            if (citr->guid == citr2->guid)
                continue;
            Player* member = sObjectMgr.GetPlayer(citr2->guid);
            uint8 onlineState = (member) ? MEMBER_STATUS_ONLINE : MEMBER_STATUS_OFFLINE;
            onlineState = onlineState | ((isBGGroup()) ? MEMBER_STATUS_PVP : 0);

            data << citr2->name;
            data << citr2->guid;
            data << uint8(onlineState);
            data << uint8(citr2->group);
            data << uint8(GetFlags(*citr2));
            data << uint8(0);
        }

        data << m_leaderGuid;
        if (GetMembersCount() - 1)
        {
            data << uint8(m_lootMethod);
            data << m_looterGuid;
            data << uint8(m_lootThreshold);
            data << uint8(m_dungeonDifficulty);
            data << uint8(m_raidDifficulty);
            data << uint8(0);
        }
        player->GetSession()->SendPacket(&data);
    }
}

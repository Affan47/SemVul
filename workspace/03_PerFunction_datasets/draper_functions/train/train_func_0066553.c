SendFriendList()
{
    Player* plr = sObjectMgr.GetPlayer(ObjectGuid(HIGHGUID_PLAYER, m_playerLowGuid));
    if (!plr)
        return;

    uint32 size = GetNumberOfSocialsWithFlag(SOCIAL_FLAG_FRIEND);

    WorldPacket data(SMSG_FRIEND_LIST, (1 + size * 25));
    data << uint8(size);

    for (PlayerSocialMap::iterator itr = m_playerSocialMap.begin(); itr != m_playerSocialMap.end(); ++itr)
    {
        if (itr->second.Flags & SOCIAL_FLAG_FRIEND)
        {
            sSocialMgr.GetFriendInfo(plr, itr->first, itr->second);

            data << ObjectGuid(HIGHGUID_PLAYER, itr->first);
            data << uint8(itr->second.Status);
            if (itr->second.Status)
            {
                data << uint32(itr->second.Area);
                data << uint32(itr->second.Level);
                data << uint32(itr->second.Class);
            }
        }
    }

    plr->GetSession()->SendPacket(&data);
    DEBUG_LOG("WORLD: Sent SMSG_FRIEND_LIST");
}

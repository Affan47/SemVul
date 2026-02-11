DelMember(ObjectGuid guid, bool isDisbanding)
{
    uint32 lowguid = guid.GetCounter();


    if (m_LeaderGuid == guid && !isDisbanding)
    {
        MemberSlot* oldLeader = NULL;
        MemberSlot* best = NULL;
        ObjectGuid newLeaderGUID;
        for (Guild::MemberList::iterator i = members.begin(); i != members.end(); ++i)
        {
            if (i->first == lowguid)
            {
                oldLeader = &(i->second);
                continue;
            }

            if (!best || best->RankId > i->second.RankId)
            {
                best = &(i->second);
                newLeaderGUID = ObjectGuid(HIGHGUID_PLAYER, i->first);
            }
        }

        if (!best)
            return true;

        SetLeader(newLeaderGUID);


        if (Player* newLeader = sObjectMgr.GetPlayer(newLeaderGUID))
            newLeader->SetRank(GR_GUILDMASTER);


        if (oldLeader)
        {
            BroadcastEvent(GE_LEADER_CHANGED, oldLeader->Name.c_str(), best->Name.c_str());
            BroadcastEvent(GE_LEFT, guid, oldLeader->Name.c_str());
        }
    }

    members.erase(lowguid);

    Player* player = sObjectMgr.GetPlayer(guid);

    if (player)
    {
        player->SetInGuild(0);
        player->SetRank(0);
    }

    CharacterDatabase.PExecute("DELETE FROM guild_member WHERE guid = '%u'", lowguid);

    if (!isDisbanding)
        UpdateAccountsNumber();

    return members.empty();
}

CheckGuildStructure()
{


    int32 GM_rights = GetRank(m_LeaderGuid);
    if (GM_rights == -1)
    {
        if (DelMember(m_LeaderGuid))
            return false;
    }
    else if (GM_rights != GR_GUILDMASTER)
        SetLeader(m_LeaderGuid);


    for (MemberList::iterator itr = members.begin(); itr != members.end(); ++itr)
        if (itr->second.RankId == GR_GUILDMASTER && m_LeaderGuid != itr->second.guid)
            itr->second.ChangeRank(GR_OFFICER);

    return true;
}

DelMember(ObjectGuid guid)
{
    for (MemberList::iterator itr = m_members.begin(); itr != m_members.end(); ++itr)
    {
        if (itr->guid == guid)
        {
            m_members.erase(itr);
            break;
        }
    }

    if (Player* player = sObjectMgr.GetPlayer(guid))
    {
        player->GetSession()->SendArenaTeamCommandResult(ERR_ARENA_TEAM_QUIT_S, GetName(), "", 0);

        for (int i = 0; i < ARENA_TEAM_END; ++i)
            player->SetArenaTeamInfoField(GetSlot(), ArenaTeamInfoType(i), 0);
    }

    CharacterDatabase.PExecute("DELETE FROM arena_team_member WHERE arenateamid = '%u' AND guid = '%u'", GetId(), guid.GetCounter());
}

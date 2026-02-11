AddMember(ObjectGuid playerGuid)
{
    std::string plName;
    uint8 plClass;


    if (GetMembersSize() >= GetMaxMembersSize())
        return false;

    Player* pl = sObjectMgr.GetPlayer(playerGuid);
    if (pl)
    {
        if (pl->GetArenaTeamId(GetSlot()))
        {
            sLog.outError("Arena::AddMember() : player already in this sized team");
            return false;
        }

        plClass = pl->getClass();
        plName = pl->GetName();
    }
    else
    {

        QueryResult* result = CharacterDatabase.PQuery("SELECT name, class FROM characters WHERE guid='%u'", playerGuid.GetCounter());
        if (!result)
            return false;

        plName = (*result)[0].GetCppString();
        plClass = (*result)[1].GetUInt8();
        delete result;


        if (Player::GetArenaTeamIdFromDB(playerGuid, GetType()) != 0)
        {
            sLog.outError("Arena::AddMember() : player %s already in this sized team", playerGuid.GetString().c_str());
            return false;
        }
    }


    Player::RemovePetitionsAndSigns(playerGuid, GetType());

    ArenaTeamMember newmember;
    newmember.name              = plName;
    newmember.guid              = playerGuid;
    newmember.Class             = plClass;
    newmember.games_season      = 0;
    newmember.games_week        = 0;
    newmember.wins_season       = 0;
    newmember.wins_week         = 0;

    int32 conf_value = sWorld.getConfig(CONFIG_INT32_ARENA_STARTPERSONALRATING);
    if (conf_value < 0)
    {
        if (sWorld.getConfig(CONFIG_UINT32_ARENA_SEASON_ID) >= 6)
        {
            if (m_stats.rating < 1000)
                newmember.personal_rating = 0;
            else
                newmember.personal_rating = 1000;
        }
        else
        {
            newmember.personal_rating = 1500;
        }
    }
    else
        newmember.personal_rating = uint32(conf_value);

    m_members.push_back(newmember);

    CharacterDatabase.PExecute("INSERT INTO arena_team_member (arenateamid, guid, personal_rating) VALUES ('%u', '%u', '%u')", m_TeamId, newmember.guid.GetCounter(), newmember.personal_rating);

    if (pl)
    {
        pl->SetInArenaTeam(m_TeamId, GetSlot(), GetType());
        pl->SetArenaTeamIdInvited(0);
        pl->SetArenaTeamInfoField(GetSlot(), ARENA_TEAM_PERSONAL_RATING, newmember.personal_rating);


        if (m_CaptainGuid != playerGuid)
            pl->SetArenaTeamInfoField(GetSlot(), ARENA_TEAM_MEMBER, 1);
    }
    return true;
}

DistributeArenaPoints()
{

    sWorld.SendWorldText(LANG_DIST_ARENA_POINTS_START);

    sWorld.SendWorldText(LANG_DIST_ARENA_POINTS_ONLINE_START);


    std::map<uint32, uint32> PlayerPoints;


    for (ObjectMgr::ArenaTeamMap::iterator team_itr = sObjectMgr.GetArenaTeamMapBegin(); team_itr != sObjectMgr.GetArenaTeamMapEnd(); ++team_itr)
    {
        if (ArenaTeam* at = team_itr->second)
        {
            at->UpdateArenaPointsHelper(PlayerPoints);
        }
    }


    for (std::map<uint32, uint32>::iterator plr_itr = PlayerPoints.begin(); plr_itr != PlayerPoints.end(); ++plr_itr)
    {

        CharacterDatabase.PExecute("UPDATE characters SET arenaPoints = arenaPoints + '%u' WHERE guid = '%u'", plr_itr->second, plr_itr->first);

        if (Player* pl = sObjectMgr.GetPlayer(ObjectGuid(HIGHGUID_PLAYER, plr_itr->first)))
            pl->ModifyArenaPoints(plr_itr->second);
    }

    PlayerPoints.clear();

    sWorld.SendWorldText(LANG_DIST_ARENA_POINTS_ONLINE_END);

    sWorld.SendWorldText(LANG_DIST_ARENA_POINTS_TEAM_START);
    for (ObjectMgr::ArenaTeamMap::iterator titr = sObjectMgr.GetArenaTeamMapBegin(); titr != sObjectMgr.GetArenaTeamMapEnd(); ++titr)
    {
        if (ArenaTeam* at = titr->second)
        {
            at->FinishWeek();
            at->SaveToDB();
            at->NotifyStatsChanged();
        }
    }

    sWorld.SendWorldText(LANG_DIST_ARENA_POINTS_TEAM_END);

    sWorld.SendWorldText(LANG_DIST_ARENA_POINTS_END);
}

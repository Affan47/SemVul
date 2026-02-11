AddPlayer(Player* plr)
{

    if (plr->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_AFK))
        { plr->ToggleAFK(); }


    ObjectGuid guid = plr->GetObjectGuid();
    Team team = plr->GetBGTeam();

    BattleGroundPlayer bp;
    bp.OfflineRemoveTime = 0;
    bp.PlayerTeam = team;


    m_Players[guid] = bp;

    UpdatePlayersCountByTeam(team, false);

    WorldPacket data;
    sBattleGroundMgr.BuildPlayerJoinedBattleGroundPacket(&data, plr);
    SendPacketToTeam(team, &data, plr, false);


    PlayerAddedToBGCheckIfBGIsRunning(plr);
    AddOrSetPlayerToCorrectBgGroup(plr, guid, team);


    DETAIL_LOG("BATTLEGROUND: Player %s joined the battle.", plr->GetName());
}

HandleBattlefieldStatusOpcode(WorldPacket& )
{

    DEBUG_LOG("WORLD: Battleground status");

    WorldPacket data;

    BattleGround* bg = NULL;
    for (uint8 i = 0; i < PLAYER_MAX_BATTLEGROUND_QUEUES; ++i)
    {
        BattleGroundQueueTypeId bgQueueTypeId = _player->GetBattleGroundQueueTypeId(i);
        if (!bgQueueTypeId)
            continue;

        BattleGroundTypeId bgTypeId = BattleGroundMgr::BGTemplateId(bgQueueTypeId);
        ArenaType arenaType = BattleGroundMgr::BGArenaType(bgQueueTypeId);

        if (bgTypeId == _player->GetBattleGroundTypeId() || (bgTypeId == BATTLEGROUND_AA && sBattleGroundMgr.IsArenaType(_player->GetBattleGroundTypeId())))
        {
            bg = _player->GetBattleGround();


            if (bg && bg->GetArenaType() == arenaType)
            {


                sBattleGroundMgr.BuildBattleGroundStatusPacket(&data, bg, i, STATUS_IN_PROGRESS, bg->GetEndTime(), bg->GetStartTime(), arenaType, _player->GetBGTeam());
                SendPacket(&data);
                continue;
            }
        }


        BattleGroundQueue& bgQueue = sBattleGroundMgr.m_BattleGroundQueues[bgQueueTypeId];
        GroupQueueInfo ginfo;
        if (!bgQueue.GetPlayerGroupInfoData(_player->GetObjectGuid(), &ginfo))
            continue;
        if (ginfo.IsInvitedToBGInstanceGUID)
        {
            bg = sBattleGroundMgr.GetBattleGround(ginfo.IsInvitedToBGInstanceGUID, bgTypeId);
            if (!bg)
                continue;
            uint32 remainingTime = WorldTimer::getMSTimeDiff(WorldTimer::getMSTime(), ginfo.RemoveInviteTime);

            sBattleGroundMgr.BuildBattleGroundStatusPacket(&data, bg, i, STATUS_WAIT_JOIN, remainingTime, 0, arenaType, TEAM_NONE);
            SendPacket(&data);
        }
        else
        {
            bg = sBattleGroundMgr.GetBattleGroundTemplate(bgTypeId);
            if (!bg)
                continue;


            PvPDifficultyEntry const* bracketEntry = GetBattlegroundBracketByLevel(bg->GetMapId(), _player->getLevel());
            if (!bracketEntry)
                continue;

            uint32 avgTime = bgQueue.GetAverageQueueWaitTime(&ginfo, bracketEntry->GetBracketId());

            sBattleGroundMgr.BuildBattleGroundStatusPacket(&data, bg, i, STATUS_WAIT_QUEUE, avgTime, WorldTimer::getMSTimeDiff(ginfo.JoinTime, WorldTimer::getMSTime()), arenaType, TEAM_NONE);
            SendPacket(&data);
        }
    }
}

SetResetSchedule(bool on)
{


    if (!HavePlayers() && !IsRaidOrHeroicDungeon())
        sMapPersistentStateMgr.GetScheduler().ScheduleReset(on, GetPersistanceState()->GetResetTime(), DungeonResetEvent(RESET_EVENT_NORMAL_DUNGEON, GetId(), Difficulty(GetSpawnMode()), GetInstanceId()));
}

Update()
{
    time_t now = time(NULL), t;
    while (!m_resetTimeQueue.empty() && (t = m_resetTimeQueue.begin()->first) < now)
    {
        DungeonResetEvent& event = m_resetTimeQueue.begin()->second;
        if (event.type == RESET_EVENT_NORMAL_DUNGEON)
        {

            m_InstanceSaves._ResetInstance(event.mapid, event.instanceId);
        }
        else
        {

            time_t resetTime = GetResetTimeFor(event.mapid, event.difficulty);
            m_InstanceSaves._ResetOrWarnAll(event.mapid, event.difficulty, event.type != RESET_EVENT_INFORM_LAST, uint32(resetTime - now));
            if (event.type != RESET_EVENT_INFORM_LAST)
            {

                event.type = ResetEventType(event.type + 1);
                ScheduleReset(true, resetTime - resetEventTypeDelay[event.type], event);
            }
            else
            {


                MapDifficultyEntry const* mapDiff = GetMapDifficultyData(event.mapid, event.difficulty);
                MANGOS_ASSERT(mapDiff);

                time_t next_reset = DungeonResetScheduler::CalculateNextResetTime(mapDiff, resetTime);

                CharacterDatabase.DirectPExecute("UPDATE instance_reset SET resettime = '" UI64FMTD "' WHERE mapid = '%u' AND difficulty = '%u'", uint64(next_reset), uint32(event.mapid), uint32(event.difficulty));

                SetResetTimeFor(event.mapid, event.difficulty, next_reset);

                ResetEventType type = RESET_EVENT_INFORM_1;
                for (; type < RESET_EVENT_INFORM_LAST; type = ResetEventType(type + 1))
                    if (next_reset > time_t(now + resetEventTypeDelay[type]))
                        break;


                event.type = type;
                ScheduleReset(true, next_reset - resetEventTypeDelay[event.type], event);
            }
        }
        m_resetTimeQueue.erase(m_resetTimeQueue.begin());
    }
}

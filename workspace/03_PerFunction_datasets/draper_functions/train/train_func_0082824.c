AddEvent(ObjectGuid const& guid, std::string title, std::string description, uint32 type, uint32 repeatable,
                                     uint32 maxInvites, int32 dungeonId, time_t eventTime, time_t , uint32 flags)
{
    Player* player = sObjectMgr.GetPlayer(guid);
    if (!player)
        return NULL;

    if (title.empty())
    {
        SendCalendarCommandResult(player, CALENDAR_ERROR_NEEDS_TITLE);
        return NULL;
    }

    if (eventTime < time(NULL))
    {
        SendCalendarCommandResult(player, CALENDAR_ERROR_INVALID_DATE);
        return NULL;
    }

    uint32 guildId = 0;

    if ((flags & CALENDAR_FLAG_GUILD_EVENT) || (flags & CALENDAR_FLAG_GUILD_ANNOUNCEMENT))
    {
        guildId = player->GetGuildId();
        if (!guildId)
        {
            SendCalendarCommandResult(player, CALENDAR_ERROR_GUILD_PLAYER_NOT_IN_GUILD);
            return NULL;
        }

        if (!CanAddGuildEvent(guildId))
        {
            SendCalendarCommandResult(player, CALENDAR_ERROR_GUILD_EVENTS_EXCEEDED);
            return NULL;
        }
    }
    else
    {
        if (!CanAddEvent(guid))
        {
            SendCalendarCommandResult(player, CALENDAR_ERROR_EVENTS_EXCEEDED);
            return NULL;
        }
    }

    uint64 nId = GetNewEventId();

    DEBUG_FILTER_LOG(LOG_FILTER_CALENDAR, "CalendarMgr::AddEvent> ID("UI64FMTD"), '%s', Desc > '%s', type=%u, repeat=%u, maxInvites=%u, dungeonId=%d, flags=%u",
                     nId, title.c_str(), description.c_str(), type, repeatable, maxInvites, dungeonId, flags);

    CalendarEvent& newEvent = m_EventStore[nId];

    newEvent.EventId = nId;
    newEvent.CreatorGuid = guid;
    newEvent.Title = title;
    newEvent.Description = description;
    newEvent.Type = (CalendarEventType) type;
    newEvent.Repeatable = (CalendarRepeatType) repeatable;
    newEvent.DungeonId = dungeonId;
    newEvent.EventTime = eventTime;
    newEvent.Flags = flags;
    newEvent.GuildId = guildId;

    CharacterDatabase.escape_string(title);
    CharacterDatabase.escape_string(description);
    CharacterDatabase.PExecute("INSERT INTO calendar_events VALUES ("UI64FMTD", %u, %u, %u, %u, %d, %u, '%s', '%s')",
                               nId,
                               guid.GetCounter(),
                               guildId,
                               type,
                               flags,
                               dungeonId,
                               uint32(eventTime),
                               title.c_str(),
                               description.c_str());
    return &newEvent;
}

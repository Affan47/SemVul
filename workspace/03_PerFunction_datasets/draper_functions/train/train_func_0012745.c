RemoveEvent(uint64 eventId, Player* remover)
{
    CalendarEventStore::iterator citr = m_EventStore.find(eventId);
    if (citr == m_EventStore.end())
    {
        SendCalendarCommandResult(remover, CALENDAR_ERROR_EVENT_INVALID);
        return;
    }

    if (remover->GetObjectGuid() != citr->second.CreatorGuid)
    {

        SendCalendarCommandResult(remover, CALENDAR_ERROR_PERMISSIONS);
        return;
    }

    SendCalendarEventRemovedAlert(&citr->second);

    CharacterDatabase.PExecute("DELETE FROM calendar_events WHERE eventId=" UI64FMTD, eventId);


    citr->second.RemoveAllInvite(remover->GetObjectGuid());
    m_EventStore.erase(citr);
}

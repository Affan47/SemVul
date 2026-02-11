AddInvite(CalendarEvent* event, ObjectGuid const& senderGuid, ObjectGuid const& inviteeGuid, CalendarInviteStatus status, CalendarModerationRank rank, std::string text, time_t statusTime)
{
    Player* sender = sObjectMgr.GetPlayer(senderGuid);
    if (!event || !sender)
        return NULL;

    std::string name;
    sObjectMgr.GetPlayerNameByGUID(inviteeGuid, name);


    if (event->GetInviteByGuid(inviteeGuid))
    {
        SendCalendarCommandResult(sender, CALENDAR_ERROR_ALREADY_INVITED_TO_EVENT_S, name.c_str());
        return NULL;
    }


    if (!event->IsGuildAnnouncement() && event->CreatorGuid != inviteeGuid)
    {
        if (!CanAddInviteTo(inviteeGuid))
        {
            SendCalendarCommandResult(sender, CALENDAR_ERROR_OTHER_INVITES_EXCEEDED_S, name.c_str());
            return NULL;
        }
    }

    CalendarInvite* invite = new CalendarInvite(event, GetNewInviteId(), senderGuid, inviteeGuid, statusTime, status, rank, text);

    if (!event->IsGuildAnnouncement())
        SendCalendarEventInvite(invite);

    if (!event->IsGuildEvent() || invite->InviteeGuid == event->CreatorGuid)
        SendCalendarEventInviteAlert(invite);

    if (event->IsGuildAnnouncement())
    {

        delete invite;
        return NULL;
    }

    DEBUG_FILTER_LOG(LOG_FILTER_CALENDAR, "Add Invite> eventId["UI64FMTD"], senderGuid[%s], inviteGuid[%s], Status[%u], rank[%u], text[%s], time[%u]",
                     event->EventId, senderGuid.GetString().c_str(), inviteeGuid.GetString().c_str(), uint32(status), uint32(rank), text.c_str(), uint32(statusTime));

    if (!event->AddInvite(invite))
    {
        sLog.outError("CalendarEvent::AddInvite > Fail adding invite!");
        delete invite;
        return NULL;
    }

    CharacterDatabase.PExecute("INSERT INTO calendar_invites VALUES ("UI64FMTD", "UI64FMTD", %u, %u, %u, %u, %u)",
                               invite->InviteId,
                               event->EventId,
                               inviteeGuid.GetCounter(),
                               senderGuid.GetCounter(),
                               uint32(status),
                               uint32(statusTime),
                               uint32(rank));

    return invite;
}

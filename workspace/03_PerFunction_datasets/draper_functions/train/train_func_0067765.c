HandleCalendarComplain(WorldPacket& recv_data)
{
    ObjectGuid guid = _player->GetObjectGuid();
    DEBUG_LOG("WORLD: Received opcode CMSG_CALENDAR_COMPLAIN [%s]", guid.GetString().c_str());

    ObjectGuid badGuyGuid;
    uint64 eventId;
    uint64 inviteId;

    recv_data >> badGuyGuid;
    recv_data >> eventId >>  inviteId;
    DEBUG_FILTER_LOG(LOG_FILTER_CALENDAR, "EventId ["UI64FMTD"], BadGuyGuid ([%s] inviteId: ["UI64FMTD"])",
                     eventId, badGuyGuid.GetString().c_str(), inviteId);


    if (sCalendarMgr.RemoveInvite(eventId, inviteId, guid))
    {
        WorldPacket data(SMSG_COMPLAIN_RESULT, 1 + 1);
        data << uint8(0);
        data << uint8(0);
        SendPacket(&data);
    }
}

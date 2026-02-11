SendCalendarRaidLockoutAdd(Player* player, DungeonPersistentState const* save)
{
    if (!save || !player)
        return;

    DEBUG_LOG("SMSG_CALENDAR_RAID_LOCKOUT_ADDED [%s]", player->GetObjectGuid().GetString().c_str());
    time_t currTime = time(NULL);

    WorldPacket data(SMSG_CALENDAR_RAID_LOCKOUT_ADDED, 4 + 4 + 4 + 4 + 8);
    data << secsToTimeBitFields(currTime);
    data << uint32(save->GetMapId());
    data << uint32(save->GetDifficulty());
    data << uint32(save->GetResetTime() - currTime);
    data << uint64(save->GetInstanceId());

    player->SendDirectMessage(&data);
}

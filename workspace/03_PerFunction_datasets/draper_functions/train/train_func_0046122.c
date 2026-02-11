BuildBattleGroundStatusPacket(WorldPacket* data, BattleGround* bg, uint8 QueueSlot, uint8 StatusID, uint32 Time1, uint32 Time2, ArenaType arenatype)
{


    if (StatusID == 0 || !bg)
    {
        data->Initialize(SMSG_BATTLEFIELD_STATUS, 4 + 8);
        *data << uint32(QueueSlot);
        *data << uint64(0);
        return;
    }

    data->Initialize(SMSG_BATTLEFIELD_STATUS, (4 + 8 + 1 + 1 + 4 + 1 + 4 + 4 + 4));
    *data << uint32(QueueSlot);

    *data << uint64(uint64(arenatype) | (uint64(0x0D) << 8) | (uint64(bg->GetTypeID()) << 16) | (uint64(0x1F90) << 48));
    *data << uint8(0);
    *data << uint8(0);
    *data << uint32(bg->GetClientInstanceID());


    *data << uint8(bg->isRated());
    *data << uint32(StatusID);
    switch (StatusID)
    {
        case STATUS_WAIT_QUEUE:
            *data << uint32(Time1);
            *data << uint32(Time2);
            break;
        case STATUS_WAIT_JOIN:
            *data << uint32(bg->GetMapId());
            *data << uint64(0);
            *data << uint32(Time1);
            break;
        case STATUS_IN_PROGRESS:
            *data << uint32(bg->GetMapId());
            *data << uint64(0);
            *data << uint32(Time1);
            *data << uint32(Time2);
            *data << uint8(0x1);
            break;
        default:
            sLog.outError("Unknown BG status!");
            break;
    }
}

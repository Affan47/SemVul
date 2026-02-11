SendLfgJoinResult(LfgJoinResult result)
{
    WorldPacket data(SMSG_LFG_JOIN_RESULT, 0);
    data << uint32(result);
    data << uint32(0);

    if (result == ERR_LFG_NO_SLOTS_PARTY)
    {
        uint8 count1 = 0;
        data << uint8(count1);
        for (uint32 i = 0; i < count1; ++i)
        {
            data << uint64(0);
            uint32 count2 = 0;
            for (uint32 j = 0; j < count2; ++j)
            {
                data << uint32(0);
                data << uint32(0);
            }
        }
    }

    SendPacket(&data);
}

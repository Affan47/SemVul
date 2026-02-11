HandleComplainOpcode(WorldPacket& recv_data)
{
    DEBUG_LOG("WORLD: Received opcode CMSG_COMPLAIN");
    recv_data.hexlike();

    uint8 spam_type;
    ObjectGuid spammerGuid;
    uint32 unk1 = 0;
    uint32 unk2 = 0;
    uint32 unk3 = 0;
    uint32 unk4 = 0;
    std::string description = "";
    recv_data >> spam_type;
    recv_data >> spammerGuid;
    switch (spam_type)
    {
        case 0:
            recv_data >> unk1;
            recv_data >> unk2;
            recv_data >> unk3;
            break;
        case 1:
            recv_data >> unk1;
            recv_data >> unk2;
            recv_data >> unk3;
            recv_data >> unk4;
            recv_data >> description;
            break;
    }


    WorldPacket data(SMSG_COMPLAIN_RESULT, 1);
    data << uint8(0);
    SendPacket(&data);

    DEBUG_LOG("REPORT SPAM: type %u, spammer %s, unk1 %u, unk2 %u, unk3 %u, unk4 %u, message %s", spam_type, spammerGuid.GetString().c_str(), unk1, unk2, unk3, unk4, description.c_str());
}

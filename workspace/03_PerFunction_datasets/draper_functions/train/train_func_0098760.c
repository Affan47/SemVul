HandleSetFactionAtWarOpcode(WorldPacket& recv_data)
{
    DEBUG_LOG("WORLD: Received opcode CMSG_SET_FACTION_ATWAR");

    uint32 repListID;
    uint8  flag;

    recv_data >> repListID;
    recv_data >> flag;

    GetPlayer()->GetReputationMgr().SetAtWar(repListID, flag);
}

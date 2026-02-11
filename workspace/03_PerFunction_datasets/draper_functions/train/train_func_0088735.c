HandleGMResponseResolveOpcode(WorldPacket& recv_data)
{

    DEBUG_LOG("WORLD: %s", recv_data.GetOpcodeName());

    sTicketMgr.Delete(GetPlayer()->GetObjectGuid());

    WorldPacket data(SMSG_GMTICKET_RESOLVE_RESPONSE, 1);
    data << uint8(0);
    SendPacket(&data);
}

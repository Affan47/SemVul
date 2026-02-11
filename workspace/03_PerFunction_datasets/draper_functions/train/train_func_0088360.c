HandleResurrectResponseOpcode(WorldPacket& recv_data)
{
    DETAIL_LOG("WORLD: Received opcode CMSG_RESURRECT_RESPONSE");

    ObjectGuid guid;
    uint8 status;
    recv_data >> guid;
    recv_data >> status;

    if (GetPlayer()->isAlive())
        return;

    if (status == 0)
    {
        GetPlayer()->clearResurrectRequestData();
        return;
    }

    if (!GetPlayer()->isRessurectRequestedBy(guid))
        return;

    GetPlayer()->ResurectUsingRequestData();
}

SendServerMessage(ServerMessageType type, const char* text , Player* player )
{
    WorldPacket data(SMSG_SERVER_MESSAGE, 50);
    data << uint32(type);
    data << text;

    if (player)
        player->GetSession()->SendPacket(&data);
    else
        SendGlobalMessage(&data);
}

HandleChatIgnoredOpcode(WorldPacket& recv_data)
{
    ObjectGuid iguid;
    uint8 unk;


    recv_data >> iguid;
    recv_data >> unk;

    Player* player = sObjectMgr.GetPlayer(iguid);
    if (!player || !player->GetSession())
        return;

    WorldPacket data;
    ChatHandler::FillMessageData(&data, this, CHAT_MSG_IGNORED, LANG_UNIVERSAL, NULL, GetPlayer()->GetObjectGuid(), GetPlayer()->GetName(), NULL);
    player->GetSession()->SendPacket(&data);
}

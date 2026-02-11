HandleOfferPetitionOpcode(WorldPacket& recv_data)
{
    DEBUG_LOG("Received opcode CMSG_OFFER_PETITION");


    ObjectGuid petitionGuid;
    ObjectGuid playerGuid;
    recv_data >> petitionGuid;
    recv_data >> playerGuid;

    Player* player = ObjectAccessor::FindPlayer(playerGuid);
    if (!player)
        { return; }

    DEBUG_LOG("OFFER PETITION: petition %s to %s", petitionGuid.GetString().c_str(), playerGuid.GetString().c_str());

    if (!sWorld.getConfig(CONFIG_BOOL_ALLOW_TWO_SIDE_INTERACTION_GUILD) && GetPlayer()->GetTeam() != player->GetTeam())
    {
        SendGuildCommandResult(GUILD_CREATE_S, "", ERR_GUILD_NOT_ALLIED);
        return;
    }

    if (player->GetGuildId())
    {
        SendGuildCommandResult(GUILD_INVITE_S, _player->GetName(), ERR_ALREADY_IN_GUILD_S);
        return;
    }

    if (player->GetGuildIdInvited())
    {
        SendGuildCommandResult(GUILD_INVITE_S, _player->GetName(), ERR_ALREADY_INVITED_TO_GUILD_S);
        return;
    }


    uint8 signs = 0;
    QueryResult* result = CharacterDatabase.PQuery("SELECT playerguid FROM petition_sign WHERE petitionguid = '%u'", petitionGuid.GetCounter());

    if (result)
        { signs = (uint8)result->GetRowCount(); }


    WorldPacket data(SMSG_PETITION_SHOW_SIGNATURES, (8 + 8 + 4 + signs + signs * 12));
    data << ObjectGuid(petitionGuid);
    data << ObjectGuid(_player->GetObjectGuid());
    data << uint32(petitionGuid.GetCounter());
    data << uint8(signs);

    for (uint8 i = 1; i <= signs; ++i)
    {
        Field* fields2 = result->Fetch();
        ObjectGuid signerGuid = ObjectGuid(HIGHGUID_PLAYER, fields2[0].GetUInt32());

        data << ObjectGuid(signerGuid);
        data << uint32(0);

        result->NextRow();
    }

    delete result;
    player->GetSession()->SendPacket(&data);
}

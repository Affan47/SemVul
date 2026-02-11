HandleGuildInfoOpcode(WorldPacket& )
{
    DEBUG_LOG("WORLD: Received opcode CMSG_GUILD_INFO");

    Guild* guild = sGuildMgr.GetGuildById(GetPlayer()->GetGuildId());
    if (!guild)
    {
        SendGuildCommandResult(GUILD_CREATE_S, "", ERR_GUILD_PLAYER_NOT_IN_GUILD);
        return;
    }

    WorldPacket data(SMSG_GUILD_INFO, (guild->GetName().size() + 4 + 4 + 4));
    data << guild->GetName();
    data << uint32(secsToTimeBitFields(guild->GetCreatedDate()));
    data << uint32(guild->GetMemberSize());
    data << uint32(guild->GetAccountsNumber());
    SendPacket(&data);
}

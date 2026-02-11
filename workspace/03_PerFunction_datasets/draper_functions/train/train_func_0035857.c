HandleGuildInviteOpcode(WorldPacket& recvPacket)
{
    DEBUG_LOG("WORLD: Received opcode CMSG_GUILD_INVITE");

    std::string Invitedname, plname;
    Player* player = NULL;

    recvPacket >> Invitedname;

    if (normalizePlayerName(Invitedname))
        player = ObjectAccessor::FindPlayerByName(Invitedname.c_str());

    if (!player)
    {
        SendGuildCommandResult(GUILD_INVITE_S, Invitedname, ERR_GUILD_PLAYER_NOT_FOUND_S);
        return;
    }

    Guild* guild = sGuildMgr.GetGuildById(GetPlayer()->GetGuildId());
    if (!guild)
    {
        SendGuildCommandResult(GUILD_CREATE_S, "", ERR_GUILD_PLAYER_NOT_IN_GUILD);
        return;
    }


    if (player->GetSocial()->HasIgnore(GetPlayer()->GetObjectGuid()))
        return;


    if (!sWorld.getConfig(CONFIG_BOOL_ALLOW_TWO_SIDE_INTERACTION_GUILD) && player->GetTeam() != GetPlayer()->GetTeam())
    {
        SendGuildCommandResult(GUILD_INVITE_S, Invitedname, ERR_GUILD_NOT_ALLIED);
        return;
    }

    if (player->GetGuildId())
    {
        plname = player->GetName();
        SendGuildCommandResult(GUILD_INVITE_S, plname, ERR_ALREADY_IN_GUILD_S);
        return;
    }

    if (player->GetGuildIdInvited())
    {
        plname = player->GetName();
        SendGuildCommandResult(GUILD_INVITE_S, plname, ERR_ALREADY_INVITED_TO_GUILD_S);
        return;
    }

    if (!guild->HasRankRight(GetPlayer()->GetRank(), GR_RIGHT_INVITE))
    {
        SendGuildCommandResult(GUILD_INVITE_S, "", ERR_GUILD_PERMISSIONS);
        return;
    }

    DEBUG_LOG("Player %s Invited %s to Join his Guild", GetPlayer()->GetName(), Invitedname.c_str());

    player->SetGuildIdInvited(GetPlayer()->GetGuildId());

    guild->LogGuildEvent(GUILD_EVENT_LOG_INVITE_PLAYER, GetPlayer()->GetObjectGuid(), player->GetObjectGuid());

    WorldPacket data(SMSG_GUILD_INVITE, (8 + 10));
    data << GetPlayer()->GetName();
    data << guild->GetName();
    player->GetSession()->SendPacket(&data);

    DEBUG_LOG("WORLD: Sent (SMSG_GUILD_INVITE)");
}

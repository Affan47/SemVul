HandleGuildDelRankOpcode(WorldPacket& )
{
    DEBUG_LOG("WORLD: Received opcode CMSG_GUILD_DEL_RANK");

    Guild* guild = sGuildMgr.GetGuildById(GetPlayer()->GetGuildId());
    if (!guild)
    {
        SendGuildCommandResult(GUILD_CREATE_S, "", ERR_GUILD_PLAYER_NOT_IN_GUILD);
        return;
    }

    if (GetPlayer()->GetObjectGuid() != guild->GetLeaderGuid())
    {
        SendGuildCommandResult(GUILD_INVITE_S, "", ERR_GUILD_PERMISSIONS);
        return;
    }

    guild->DelRank();

    guild->Query(this);
    guild->Roster();
}

HandleGuildEventLogQueryOpcode(WorldPacket& )
{

    DEBUG_LOG("WORLD: Received (MSG_GUILD_EVENT_LOG_QUERY)");

    if (uint32 GuildId = GetPlayer()->GetGuildId())
        if (Guild* pGuild = sGuildMgr.GetGuildById(GuildId))
            pGuild->DisplayGuildEventLog(this);
}

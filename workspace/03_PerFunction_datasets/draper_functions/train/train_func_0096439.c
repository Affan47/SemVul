LoadGuilds()
{
    Guild* newGuild;
    uint32 count = 0;


    QueryResult* result = CharacterDatabase.Query("SELECT guild.guildid,guild.name,leaderguid,EmblemStyle,EmblemColor,BorderStyle,BorderColor,"

                          "BackgroundColor,info,motd,createdate FROM guild ORDER BY guildid ASC");

    if (!result)
    {
        BarGoLink bar(1);

        bar.step();

        sLog.outString();
        sLog.outString(">> Loaded %u guild definitions", count);
        return;
    }


    QueryResult* guildRanksResult   = CharacterDatabase.Query("SELECT guildid,rid,rname,rights FROM guild_rank ORDER BY guildid ASC, rid ASC");


    QueryResult* guildMembersResult = CharacterDatabase.Query("SELECT guildid,guild_member.guid,rank,pnote,offnote,"

                                      "characters.name, characters.level, characters.class, characters.zone, characters.logout_time, characters.account "
                                      "FROM guild_member LEFT JOIN characters ON characters.guid = guild_member.guid ORDER BY guildid ASC");

    BarGoLink bar(result->GetRowCount());

    do
    {


        bar.step();
        ++count;

        newGuild = new Guild;
        if (!newGuild->LoadGuildFromDB(result) ||
            !newGuild->LoadRanksFromDB(guildRanksResult) ||
            !newGuild->LoadMembersFromDB(guildMembersResult) ||
            !newGuild->CheckGuildStructure()
           )
        {
            newGuild->Disband();
            delete newGuild;
            continue;
        }
        newGuild->LoadGuildEventLogFromDB();
        AddGuild(newGuild);
    }
    while (result->NextRow());

    delete result;
    delete guildRanksResult;
    delete guildMembersResult;


    CharacterDatabase.PExecute("DELETE FROM guild_eventlog WHERE LogGuid > '%u'", sWorld.getConfig(CONFIG_UINT32_GUILD_EVENT_LOG_COUNT));

    sLog.outString();
    sLog.outString(">> Loaded %u guild definitions", count);
}

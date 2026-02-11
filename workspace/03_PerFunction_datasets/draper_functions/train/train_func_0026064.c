LoadDBVersion()
{
    QueryResult* result = WorldDatabase.Query("SELECT version, creature_ai_version FROM db_version LIMIT 1");
    if (result)
    {
        Field* fields = result->Fetch();

        m_DBVersion              = fields[0].GetCppString();
        m_CreatureEventAIVersion = fields[1].GetCppString();

        delete result;
    }

    if (m_DBVersion.empty())
        { m_DBVersion = "Unknown world database."; }

    if (m_CreatureEventAIVersion.empty())
        { m_CreatureEventAIVersion = "Unknown creature EventAI."; }
}

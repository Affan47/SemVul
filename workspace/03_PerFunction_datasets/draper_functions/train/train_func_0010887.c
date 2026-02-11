LoadScriptNames()
{
    m_scriptNames.push_back("");
    QueryResult* result = WorldDatabase.Query(
                              "SELECT DISTINCT(ScriptName) FROM creature_template WHERE ScriptName <> '' "
                              "UNION "
                              "SELECT DISTINCT(ScriptName) FROM gameobject_template WHERE ScriptName <> '' "
                              "UNION "
                              "SELECT DISTINCT(ScriptName) FROM item_template WHERE ScriptName <> '' "
                              "UNION "
                              "SELECT DISTINCT(ScriptName) FROM scripted_areatrigger WHERE ScriptName <> '' "
                              "UNION "
                              "SELECT DISTINCT(ScriptName) FROM scripted_event_id WHERE ScriptName <> '' "
                              "UNION "
                              "SELECT DISTINCT(ScriptName) FROM instance_template WHERE ScriptName <> '' "
                              "UNION "
                              "SELECT DISTINCT(ScriptName) FROM world_template WHERE ScriptName <> ''");

    if (!result)
    {
        BarGoLink bar(1);
        bar.step();
        sLog.outErrorDb(">> Loaded empty set of Script Names!");
        sLog.outString();
        return;
    }

    BarGoLink bar(result->GetRowCount());
    uint32 count = 0;

    do
    {
        bar.step();
        m_scriptNames.push_back((*result)[0].GetString());
        ++count;
    }
    while (result->NextRow());
    delete result;

    std::sort(m_scriptNames.begin(), m_scriptNames.end());

    sLog.outString(">> Loaded %d Script Names", count);
    sLog.outString();
}

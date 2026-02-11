LoadEventIdScripts()
{
    m_EventIdScripts.clear();
    QueryResult* result = WorldDatabase.Query("SELECT id, ScriptName FROM scripted_event_id");

    uint32 count = 0;

    if (!result)
    {
        BarGoLink bar(1);
        bar.step();
        sLog.outString(">> Loaded %u scripted event id", count);
        sLog.outString();
        return;
    }

    BarGoLink bar(result->GetRowCount());

    std::set<uint32> eventIds;
    CollectPossibleEventIds(eventIds);

    do
    {
        ++count;
        bar.step();

        Field* fields = result->Fetch();

        uint32 eventId          = fields[0].GetUInt32();
        const char* scriptName  = fields[1].GetString();

        std::set<uint32>::const_iterator itr = eventIds.find(eventId);
        if (itr == eventIds.end())
            sLog.outErrorDb("Table `scripted_event_id` has id %u not referring to any gameobject_template type 10 data2 field, type 3 data6 field, type 13 data 2 field, type 29 or any spell effect %u or path taxi node data",
                            eventId, SPELL_EFFECT_SEND_EVENT);

        m_EventIdScripts[eventId] = GetScriptId(scriptName);
    }
    while (result->NextRow());

    delete result;

    sLog.outString(">> Loaded %u scripted event id", count);
    sLog.outString();
}

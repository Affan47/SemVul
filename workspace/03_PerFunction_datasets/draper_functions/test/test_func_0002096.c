ApplyNewEvent(uint16 event_id, bool resume)
{
    m_ActiveEvents.insert(event_id);
    CharacterDatabase.PExecute("INSERT INTO game_event_status (event) VALUES (%u)", event_id);

    if (sWorld.getConfig(CONFIG_BOOL_EVENT_ANNOUNCE))
        sWorld.SendWorldText(LANG_EVENTMESSAGE, mGameEvent[event_id].description.c_str());

    sLog.outString("GameEvent %u \"%s\" started.", event_id, mGameEvent[event_id].description.c_str());

    GameEventSpawn(event_id);

    int16 event_nid = (-1) * event_id;
    GameEventUnspawn(event_nid);

    UpdateCreatureData(event_id, true);

    UpdateEventQuests(event_id, true);
    UpdateWorldStates(event_id, true);


    if (!resume)
        SendEventMails(event_id);
}

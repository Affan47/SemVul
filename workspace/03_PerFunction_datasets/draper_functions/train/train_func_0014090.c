HandleEventListCommand(char* args)
{
    uint32 counter = 0;
    bool all = false;
    std::string arg = args;
    if (arg == "all")
        { all = true; }

    GameEventMgr::GameEventDataMap const& events = sGameEventMgr.GetEventMap();

    char const* active = GetMangosString(LANG_ACTIVE);
    char const* inactive = GetMangosString(LANG_FACTION_INACTIVE);
    char const* state = "";

    for (uint32 event_id = 0; event_id < events.size(); ++event_id)
    {
        if (!sGameEventMgr.IsValidEvent(event_id))
            { continue; }

        if (!sGameEventMgr.IsActiveEvent(event_id))
        {
            if (!all)
                { continue; }
            state = inactive;
        }
        else
            { state = active; }

        GameEventData const& eventData = events[event_id];

        if (m_session)
            { PSendSysMessage(LANG_EVENT_ENTRY_LIST_CHAT, event_id, event_id, eventData.description.c_str(), state); }
        else
            { PSendSysMessage(LANG_EVENT_ENTRY_LIST_CONSOLE, event_id, eventData.description.c_str(), state); }

        ++counter;
    }

    if (counter == 0)
        { SendSysMessage(LANG_NOEVENTFOUND); }

    return true;
}

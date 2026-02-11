LoadGameObjectTemplateScripts()
{
    LoadScripts(sGameObjectTemplateScripts, "dbscripts_on_go_template_use");


    for (ScriptMapMap::const_iterator itr = sGameObjectTemplateScripts.second.begin(); itr != sGameObjectTemplateScripts.second.end(); ++itr)
    {
        if (!sObjectMgr.GetGameObjectInfo(itr->first))
            sLog.outErrorDb("Table `dbscripts_on_go_template_use` has not existing gameobject (Entry: %u) as script id", itr->first);
    }
}

RemoveObsoleteParsers()
{
    TRACE(_T("NativeParser::RemoveObsoleteParsers(): Enter"));

    ConfigManager* cfg = Manager::Get()->GetConfigManager(_T("code_completion"));
    const size_t maxParsers = cfg->ReadInt(_T("/max_parsers"), 5);
    wxArrayString removedProjectNames;
    std::pair<cbProject*, ParserBase*> info = GetParserInfoByCurrentEditor();

    while (m_ParserList.size() > maxParsers)
    {
        bool deleted = false;
        for (ParserList::const_iterator it = m_ParserList.begin(); it != m_ParserList.end(); ++it)
        {
            if (it->second == info.second)
                continue;

            wxString prj = (it->first ? it->first->GetTitle() : _T("*NONE*"));
            if ( DeleteParser(it->first) )
            {


                removedProjectNames.Add(prj);
                deleted = true;
                break;
            }
        }

        if (!deleted)
            break;
    }

    for (size_t i = 0; i < removedProjectNames.GetCount(); ++i)
    {
        wxString log(F(_("NativeParser::RemoveObsoleteParsers():Removed obsolete parser of '%s'"), removedProjectNames[i].wx_str()));
        CCLogger::Get()->Log(log);
        CCLogger::Get()->DebugLog(log);
    }

    TRACE(_T("NativeParser::RemoveObsoleteParsers(): Leave"));
}

DetectDBCLang()
{
    uint32 m_lang_confid = sConfig.GetIntDefault("DBC.Locale", 255);

    if (m_lang_confid != 255 && m_lang_confid >= MAX_LOCALE)
    {
        sLog.outError("Incorrect DBC.Locale! Must be >= 0 and < %d (set to 0)", MAX_LOCALE);
        m_lang_confid = LOCALE_enUS;
    }

    ChrRacesEntry const* race = sChrRacesStore.LookupEntry(RACE_HUMAN);
    MANGOS_ASSERT(race);

    std::string availableLocalsStr;

    uint32 default_locale = MAX_LOCALE;
    for (int i = MAX_LOCALE - 1; i >= 0; --i)
    {
        if (strlen(race->name[i]) > 0)
        {
            default_locale = i;
            m_availableDbcLocaleMask |= (1 << i);
            availableLocalsStr += localeNames[i];
            availableLocalsStr += " ";
        }
    }

    if (default_locale != m_lang_confid && m_lang_confid < MAX_LOCALE &&
        (m_availableDbcLocaleMask & (1 << m_lang_confid)))
    {
        default_locale = m_lang_confid;
    }

    if (default_locale >= MAX_LOCALE)
    {
        sLog.outError("Unable to determine your DBC Locale! (corrupt DBC?)");
        Log::WaitBeforeContinueIfNeed();
        exit(1);
    }

    m_defaultDbcLocale = LocaleConstant(default_locale);

    sLog.outString("Using %s DBC Locale as default. All available DBC locales: %s", localeNames[m_defaultDbcLocale], availableLocalsStr.empty() ? "<none>" : availableLocalsStr.c_str());
    sLog.outString();
}

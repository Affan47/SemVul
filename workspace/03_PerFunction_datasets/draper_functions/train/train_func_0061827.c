configObject()
    {
        if (!config) {
            config = new KConfig(QLatin1String("kdebugrc"), KConfig::NoGlobals);
            m_disableAll = config->group(QString()).readEntry("DisableAll", false);
        }
        return config;
    }

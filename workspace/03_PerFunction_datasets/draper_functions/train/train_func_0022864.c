load()
{
    QSettings settings;
    settings.beginGroup(QLatin1String("toolbarsearch"));
    m_recentSearches = settings.value(QLatin1String("recentSearches")).toStringList();
    m_maxSavedSearches = settings.value(QLatin1String("maximumSaved"), m_maxSavedSearches).toInt();

    m_suggestionsEnabled = settings.value(QLatin1String("useSuggestions"), true).toBool();
    if (m_suggestionsEnabled) {
        connect(this, SIGNAL(textEdited(const QString &)),
                this, SLOT(textEdited(const QString &)));
    }

    settings.endGroup();
    setupList();
}

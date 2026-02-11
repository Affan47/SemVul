currentEngineChanged()
{
    OpenSearchEngine *newEngine = openSearchManager()->currentEngine();
    Q_ASSERT(newEngine);
    if (!newEngine)
        return;

    if (m_suggestionsEnabled) {
        if (openSearchManager()->engineExists(m_currentEngine)) {
            OpenSearchEngine *oldEngine = openSearchManager()->engine(m_currentEngine);
            disconnect(oldEngine, SIGNAL(suggestions(const QStringList &)),
                       this, SLOT(newSuggestions(const QStringList &)));
        }

        connect(newEngine, SIGNAL(suggestions(const QStringList &)),
                this, SLOT(newSuggestions(const QStringList &)));
    }

    setInactiveText(newEngine->name());
    m_currentEngine = newEngine->name();
    m_suggestions.clear();
    setupList();
}

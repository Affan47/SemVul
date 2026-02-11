removeEngine(const QString &name)
{
    if (m_engines.count() <= 1)
        return;

    if (!m_engines.contains(name))
        return;

    OpenSearchEngine *engine = m_engines[name];
    foreach (const QString &keyword, m_keywords.keys(engine))
        m_keywords.remove(keyword);
    engine->deleteLater();

    m_engines[name] = 0;
    m_engines.remove(name);

    QString file = QDir(enginesDirectory()).filePath(generateEngineFileName(name));
    QFile::remove(file);

    if (name == m_current)
        setCurrentEngineName(m_engines.keys().at(0));

    emit changed();
}

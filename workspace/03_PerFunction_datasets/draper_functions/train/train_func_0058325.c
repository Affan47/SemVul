detailDefinitions(const QString& contactType, QContactManager::Error* error) const
{

    if (d->m_definitions.isEmpty()) {
        d->m_definitions = QContactManagerEngine::schemaDefinitions();
    }

    *error = QContactManager::NoError;
    return d->m_definitions.value(contactType);
}

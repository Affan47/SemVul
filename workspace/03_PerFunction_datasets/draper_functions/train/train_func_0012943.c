saveRelationships(QList<QContactRelationship>* relationships, QMap<int, QContactManager::Error>* errorMap, QContactManager::Error* error)
{
    *error = QContactManager::NoError;
    QContactManager::Error functionError;
    QContactChangeSet changeSet;

    for (int i = 0; i < relationships->size(); i++) {
        QContactRelationship curr = relationships->at(i);
        saveRelationship(&curr, changeSet, &functionError);
        if (functionError != QContactManager::NoError && errorMap)
            errorMap->insert(i, functionError);


        relationships->replace(i, curr);


        if (functionError != QContactManager::NoError)
            *error = functionError;
    }

    d->emitSharedSignals(&changeSet);
    return (*error == QContactManager::NoError);
}

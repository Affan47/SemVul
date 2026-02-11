toString() const
{
    QString mgrName;
    QMap<QString, QString> params;
    QString engineId;

    if (d) {
        QOrganizerManager::parseUri(d->managerUri(), &mgrName, &params);
        engineId = d->toString();
    }


    return buildIdString(mgrName, params, engineId);
}

createEngine(const QString &managerName, const QMap<QString,QString> &parameters)
{
    Q_Q(QLandmarkManager);

    if (!q->availableManagers().contains(managerName)) {
        errorCode = QLandmarkManager::InvalidManagerError;
        errorString = QString("The landmark manager, %1, was not found").arg(managerName);
        qWarning() << errorString;
        engine = 0;
        return;
    }

    QList<QLandmarkManagerEngineFactory *> factories = QLandmarkManagerPrivate::factories().values(managerName);

    bool ok;
    int implementationVersion = parameters.value(QTLANDMARKS_IMPLEMENTATION_VERSION_NAME).toInt(&ok);
    if (!ok)
        implementationVersion = -1;

    foreach(QLandmarkManagerEngineFactory *f, factories)
    {
        QList<int> versions = f->supportedImplementationVersions();
            if (implementationVersion == -1
               || versions.isEmpty()
               || versions.contains(implementationVersion)) {
                    engine = f->engine(parameters, &errorCode, &errorString);
                    break;
               }
    }

    if (!engine) {
        if (errorCode == QLandmarkManager::NoError) {
            errorCode = QLandmarkManager::InvalidManagerError;
            errorString = "The landmark manager could not return the requested engine instance";
        }
    }
}

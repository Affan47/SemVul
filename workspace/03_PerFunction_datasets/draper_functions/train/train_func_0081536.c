allStaleFiles(const QString &applicationName)
{
    KGlobal::dirs()->addResourceType("stale", 0, QString::fromLatin1("data/stalefiles"));

    QString appName(applicationName);
    if (appName.isEmpty()) {
        appName = QCoreApplication::instance()->applicationName();
    }


    const QStringList files = KGlobal::dirs()->findAllResources("stale", appName + QLatin1String("/*"));

    QList<KAutoSaveFile *> list;


    foreach(QString file, files) {
        if (file.endsWith(QLatin1String(".lock")))
            continue;
        const QString sep = file.right(3);
        file.chop(KAutoSaveFilePrivate::padding);

        int sepPos = file.indexOf(sep);
        int pathPos = file.indexOf(QChar::fromLatin1('_'), sepPos);
        KUrl name;
        name.setProtocol(file.mid(sepPos + 3, pathPos - sep.size() - 3));
        name.setPath(KUrl::fromPercentEncoding(file.right(pathPos - 1).toLatin1()));
        name.addPath(KUrl::fromPercentEncoding(file.left(sepPos).toLatin1()));


        KAutoSaveFile* asFile = new KAutoSaveFile(name);
        asFile->setFileName(file);

        asFile->d->managedFileNameChanged = false;
        list.append(asFile);
    }

    return list;
}

restore(const KConfigGroup &config)
{
    const QStringList cfgList = config.readEntry("LaunchCounts", QStringList());

    const QRegExp r("(\\d*) (.*)");
    foreach (const QString& entry, cfgList) {
        r.indexIn(entry);
        int count = r.cap(1).toInt();
        QString id = r.cap(2);
        d->launchCounts[id] = count;
    }
}

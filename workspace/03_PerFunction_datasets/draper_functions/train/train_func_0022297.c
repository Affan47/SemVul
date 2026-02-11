load(const QString &themename)
{
    QString prefix = QDir::toNativeSeparators(Config::getInstance()->plexydeskBasePath() +
            QLatin1String("/share/plexy/themepack/") +
            themename
            + QLatin1String("/resources/"));

    QDir dir(prefix);
    dir.setFilter(QDir::Files);
    dir.setNameFilters(QStringList() << "*.svg" << "*.svgz");
    QFileInfoList list = dir.entryInfoList();

    for (int i = 0; i < list.size(); i++)
    {
        QFileInfo file = list.at(i);
        d->map[file.completeBaseName()] = QPixmap(QDir::toNativeSeparators(file.absoluteFilePath()));
        d->fileHash[file.completeBaseName()] = file.absoluteFilePath();
    }
}

loadSettings()
{
    QSettings settings;
    settings.beginGroup(QLatin1String("network"));
    qint64 maximumCacheSize = settings.value(QLatin1String("maximumCacheSize"), 50).toInt();
    maximumCacheSize = maximumCacheSize * 1024 * 1024;
    setMaximumCacheSize(maximumCacheSize);
}

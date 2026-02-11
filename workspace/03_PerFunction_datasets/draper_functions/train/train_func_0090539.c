allowedRunners() const
{
    KConfigGroup config = d->configGroup();
    return config.readEntry("pluginWhiteList", QStringList());
}

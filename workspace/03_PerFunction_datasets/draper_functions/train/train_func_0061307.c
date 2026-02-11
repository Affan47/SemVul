newTheme(const QString &name, const KService::Ptr &service)
{
    KEmoticonsProvider *provider = d->loadProvider(service);
    KEmoticonsTheme theme(provider);
    theme.setThemeName(name);

    theme.createNew();

    return theme;
}

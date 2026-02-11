fromFiles(const QStringList &files, const KConfigGroup &config)
{
    QList<KPluginInfo> infolist;
    for( QStringList::ConstIterator it = files.begin(); it != files.end(); ++it )
    {
        KPluginInfo info(*it);
        info.setConfig(config);
        infolist += info;
    }
    return infolist;
}

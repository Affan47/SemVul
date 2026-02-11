setRequestMetaData(const QString &key, const QString &value)
{
    KIO::Integration::AccessManager *manager = qobject_cast<KIO::Integration::AccessManager *>(networkAccessManager());
    if (manager)
        manager->requestMetaData()[key] = value;
}

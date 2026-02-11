createJob(const QString &operation, QMap<QString, QVariant> &parameters)
{
    if (m_clientName.isEmpty()) {
        return 0;
    }

    return new StorageJob(m_clientName, operation, parameters, this);
}

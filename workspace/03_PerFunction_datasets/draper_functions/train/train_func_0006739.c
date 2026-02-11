allDevices()
{
    if (d->cacheSynced)
    {
        return d->devicesCache;
    }

    QDBusReply<QStringList> reply = d->manager.call("GetAllDevices");

    if (!reply.isValid())
    {
        qWarning() << Q_FUNC_INFO << " error: " << reply.error().name() << endl;
        return QStringList();
    }

    d->devicesCache = reply;
    d->cacheSynced = true;

    return reply;
}

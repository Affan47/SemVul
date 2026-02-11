checkCache(const QString &key)
{
    if (cacheSynced) {
        if (key.isEmpty()) {
            if (invalidKeys.isEmpty()) {
                return;
            }
        } else if (!invalidKeys.contains(key)) {
            return;
        }
    }

    QDBusReply<QVariantMap> reply = device.call("GetAllProperties");

    if (reply.isValid()) {
        cache = reply;
    } else {
        qWarning() << Q_FUNC_INFO << " error: " << reply.error().name()
            << ", " << reply.error().message() << endl;
        cache = QVariantMap();
    }

    invalidKeys.clear();
    cacheSynced = true;

}

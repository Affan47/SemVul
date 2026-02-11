setFirstDateTime()
{

    QGeoPositionInfo update;
    bool hasFix = false;
    while (m_proxy->m_device->bytesAvailable() > 0) {
        char buf[1024];
        qint64 size = m_proxy->m_device->readLine(buf, sizeof(buf));
        if (size <= 0)
            continue;
        bool ok = m_proxy->parsePosInfoFromNmeaData(buf, size, &update, &hasFix);
        if (ok && update.timestamp().isValid()) {
            QPendingGeoPositionInfo pending;
            pending.info = update;
            pending.hasFix = hasFix;
            m_pendingUpdates.enqueue(pending);
            return true;
        }
    }
    return false;
}

canRead(QIODevice *device)
{
    if (!device) {
        qWarning("EPSHandler::canRead() called with no device");
        return false;
    }

    qint64 oldPos = device->pos();

    QByteArray head = device->readLine(64);
    int readBytes = head.size();
    if (device->isSequential()) {
        while (readBytes > 0)
            device->ungetChar(head[readBytes-- - 1]);
    } else {
        device->seek(oldPos);
    }

    return head.contains("%!PS-Adobe");
}

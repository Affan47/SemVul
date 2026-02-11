create(QIODevice *device, const QByteArray &format) const
{
    QImageIOHandler *handler = new DDSHandler;
    handler->setDevice(device);
    handler->setFormat(format);
    return handler;
}

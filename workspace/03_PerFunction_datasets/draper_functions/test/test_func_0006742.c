setSuspended(bool enable)
{
    if (state != Connected)
        return;
    Q_ASSERT(socket);
    Q_ASSERT(!localServer);

    if (enable) {

        socket->setReadBufferSize(1);
    } else {

        socket->setReadBufferSize(StandardBufferSize);
        if (socket->bytesAvailable() >= HeaderSize) {

            QMetaObject::invokeMethod(this, "socketReadyRead", Qt::QueuedConnection);
        }


        QByteArray data = socket->read(socket->bytesAvailable() + 1);
        for (int i = data.size(); --i >= 0; )
            socket->ungetChar(data[i]);
    }
}

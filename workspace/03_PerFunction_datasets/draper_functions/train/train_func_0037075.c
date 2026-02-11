sendMessage(const QByteArray &message, int waitMsecsForReply)
{
#ifdef SINGALAPPLICATION_DEBUG
    qDebug() << "SingleApplication::" << __FUNCTION__ << message << waitMsecsForReply;
#endif
    QLocalSocket socket;
    socket.connectToServer(serverName());
    if (!socket.waitForConnected(500))
        return false;
    socket.write(message);
    socket.flush();
    socket.waitForBytesWritten();
    bool success = true;
    if (socket.error() != QLocalSocket::UnknownSocketError) {
#ifdef SINGALAPPLICATION_DEBUG
        qDebug() << "SingleApplication::" << __FUNCTION__ << socket.errorString();
#endif
        success = false;
    }
    if (success) {
        socket.waitForReadyRead(waitMsecsForReply);
        if (socket.bytesAvailable() > 0)
            emit messageReceived(&socket);
    }
    return success;
}

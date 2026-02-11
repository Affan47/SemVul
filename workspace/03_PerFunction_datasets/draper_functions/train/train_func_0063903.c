synchronousConnectToHost(const QString &protocol, const QString &host,
                                                     quint16 port, int msecs, QObject *parent)
{
    QTcpSocket *socket = connectToHost(protocol, host, port, parent);
    if (!socket->waitForConnected(msecs))
        setError(socket, QAbstractSocket::SocketTimeoutError,
                 i18n("Timed out trying to connect to remote host"));
    return socket;
}

sendToInstance( const QString& data, MooseEnums::StartNewInstanceBehaviour behaviour )
{
    LOGL( 3, "sendToInstance (new instance): " << data );

    QTcpSocket socket;
    socket.connectToHost( QHostAddress::LocalHost, The::settings().controlPort() );

    if ( socket.waitForConnected( 500 ) )
    {
        if ( data.length() > 0 )
        {
            QByteArray utf8Data = data.toUtf8();
            socket.write( utf8Data, utf8Data.length() );
            socket.flush();
        }

        socket.close();
        return true;
    }
    else if ( behaviour == MooseEnums::StartNewInstance )
    {
        qDebug() << "Starting instance" << The::settings().path();

        return QProcess::startDetached( The::settings().path(), QStringList() << data );
    }

    return false;
}

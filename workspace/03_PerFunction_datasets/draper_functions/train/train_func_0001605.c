run()
{
    m_serverSocket = new QTcpServer;

    connect(this, SIGNAL(messageReceived(int,Jolie::Message)),
            m_server, SLOT(messageReceived(int,Jolie::Message)));
    connect(m_serverSocket, SIGNAL(newConnection()),
            this, SLOT(onIncomingConnection()), Qt::QueuedConnection);

    m_serverSocket->listen(QHostAddress::Any, m_port);

    exec();

    delete m_serverSocket;
}

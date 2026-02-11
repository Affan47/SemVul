slotSocketError(QAbstractSocket::SocketError error)
{
    Q_UNUSED(error);


    delete m_socket;
    m_socket = NULL;


}

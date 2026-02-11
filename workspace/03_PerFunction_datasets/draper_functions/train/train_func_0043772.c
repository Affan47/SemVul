nickName() const
{
    return QString(peerManager->userName()) + '@' + QHostInfo::localHostName()
           + ':' + QString::number(server.serverPort());
}

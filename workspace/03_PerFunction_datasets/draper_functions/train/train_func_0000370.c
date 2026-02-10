TcpReadFromProxy()
  {
    if(!_running) {
      qDebug("SOCKS read but not running");
      return;
    }

    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if(!socket) {
      qWarning("SOCKS Illegal call to ReadFromClient()");
      return;
    }

    if(!CheckSession()) {
      qDebug("SOCKS read but no session");
      return;
    }

    do {
      QByteArray data = socket->read(64000);
      qDebug() << "SOCKS Read" << data.count() << "bytes from proxy socket";
      TcpResponsePacket resp(_table.IdForConnection(socket), data);


      SendReply(resp.ToByteArray());
    } while(socket->bytesAvailable());

    qDebug() << "MEM active" << _table.Count();
  }

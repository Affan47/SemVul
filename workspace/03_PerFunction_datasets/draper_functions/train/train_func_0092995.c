HandleDisconnect()
  {
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if(socket == 0) {
      qCritical() << "HandleDisconnect signal received a non-socket";
      return;
    }
    HandleSocketClose(socket, "Disconnected");
  }

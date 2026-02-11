CloseSocket(QAbstractSocket* socket)
  {
    if(_table.ContainsConnection(socket)) {
      SendReply(FinishPacket(_table.IdForConnection(socket)).ToByteArray());
    }

    if(socket && socket->isOpen()) socket->close();

    _table.ConnectionClosed(socket);
    _tcp_buffers.remove(socket);
    if(_timers.contains(socket)) {
      _timers_map.remove(_timers[socket].data());
    }
    _timers.remove(socket);

    if(socket) socket->deleteLater();
  }

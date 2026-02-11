HandleSessionPacket(QSharedPointer<Packet> pp)
  {
    if(!_running) return;
    if(pp.isNull()) return;

    qDebug() << "SOCKS MEM active" << _table.Count();
    Packet::PacketType ptype = pp->GetType();
    switch(ptype) {
      case Packet::PacketType_TcpStart:
        TcpCreateProxy(pp);
        return;
      case Packet::PacketType_UdpStart:
        qDebug() << "SOCKS got UDP start packet";
        UdpCreateProxy(pp);
        return;
      case Packet::PacketType_TcpRequest:
        TcpHandleRequest(pp);
        return;
      case Packet::PacketType_UdpRequest:
        qDebug() << "SOCKS got UDP request packet";
        UdpHandleRequest(pp);
        return;
      case Packet::PacketType_TcpResponse:
        return;
      case Packet::PacketType_UdpResponse:
        return;
      case Packet::PacketType_Finish:
        HandleFinish(pp);
        return;
      default:
        qWarning() << "SOCKS Unknown packet type" << ptype;
    }
  }

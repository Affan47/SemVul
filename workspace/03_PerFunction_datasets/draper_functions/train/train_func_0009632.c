UdpHandleRequest(QSharedPointer<Packet> packet)
  {
    UdpRequestPacket *req = dynamic_cast<UdpRequestPacket*>(packet.data());
    if(!req) return;

    qDebug() << "SOCKS Handling UDP requst";

    QByteArray cid = req->GetConnectionId();
    if(!_table.ContainsId(cid)) {
      qDebug() << "SOCKS Ignoring request packet for other relay" << cid;
      return;
    }

    QUdpSocket *socket = qobject_cast<QUdpSocket*>(_table.ConnectionForId(cid));
    if(!socket) {
      qWarning() << "Could not cast to QUdpSocket";
      return;
    }

    SocksHostAddress peer = req->GetHostName();
    QByteArray sig = req->GetSignature();
    QByteArray data = req->GetRequestData();

    qDebug() << "SOCKS VERIFY SIGB" << sig;
    QByteArray to_verify = peer.ToString().toAscii() + data;
    if(!_table.VerifyConnectionBytes(cid, to_verify, sig)) {
      qWarning() << "SOCKS Verification failed sig:" << sig.count() << "data:" << data.count() << "CID" << cid;
      return;
    }


    _timers[socket]->start();

    if(req->GetHostName().IsHostName()) {
      qDebug() << "SOCKS UDP Hostname" << req->GetHostName().GetName();
      int lookup_id = QHostInfo::lookupHost(req->GetHostName().GetName(),
          this, SLOT(TcpDnsLookupFinished(const QHostInfo &)));
      UdpPendingDnsData dns_data = {socket, req->GetHostName().GetPort(), data};
      _udp_pending_dns[lookup_id] = dns_data;
    } else {
      qDebug() << "SOCKS UDP writeDatagram " << req->GetHostName().GetAddress() <<":"
        << req->GetHostName().GetPort() << (req->GetHostName().IsHostName() ? "DNS" : "Address");
      socket->writeDatagram(data, req->GetHostName().GetAddress(), req->GetHostName().GetPort());
    }

    qDebug() << "SOCKS MEM active" << _table.Count();
  }

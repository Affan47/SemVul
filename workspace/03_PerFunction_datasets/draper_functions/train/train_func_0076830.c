HandleTcpResponse(QSharedPointer<Packet> pp)
  {
    TcpResponsePacket *rp = dynamic_cast<TcpResponsePacket*>(pp.data());
    if(!rp) {
      qWarning() << "SOCKS Could not cast TcpResponsePacket";
      return;
    }
    qDebug() << "SOCKS response : " << rp->GetResponseData().count();
    TryWrite(rp->GetResponseData());
  }

SessionData(const QByteArray &bytes)
  {
    qDebug() << "SOCKS SESSION DATA";
    if(!_running) return;

    QByteArray rest = bytes;
    int bytes_read = 0;
    while(rest.count()) {
      QSharedPointer<Packet> pp(Packet::ReadPacket(rest, bytes_read));

      if(!bytes_read) break;
      rest = rest.mid(bytes_read);

      if(pp.isNull()) continue;
      qDebug() << "SOCKS Got packet of type" << pp->GetType() << "Read bytes:" << bytes_read;
      HandleSessionPacket(pp);
    }
    qDebug() << "SOCKS MEM active" << _table.Count();
  }

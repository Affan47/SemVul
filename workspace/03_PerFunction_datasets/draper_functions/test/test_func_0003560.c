HandleConnection(const QSharedPointer<Connection> &con)
  {
    const Address &addr = con->GetEdge()->GetRemotePersistentAddress();
    if(!_remote_endpoints.contains(addr)) {
      _remote_endpoints.append(addr);
    }

    QObject::connect(con.data(), SIGNAL(Disconnected(const QString &)),
        this, SLOT(HandleDisconnect(const QString &)));
  }

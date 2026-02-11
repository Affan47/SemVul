IncomingData(const Request &notification)
  {
    if(Stopped()) {
      qWarning() << "Received a message on a closed session:" << ToString();
      return;
    }

    QSharedPointer<Connections::IOverlaySender> sender =
      notification.GetFrom().dynamicCast<Connections::IOverlaySender>();

    if(!sender) {
      qDebug() << ToString() << " received wayward message from: " <<
        notification.GetFrom()->ToString();
      return;
    }

    const Id &id = sender->GetRemoteId();
    if(!_group.Contains(id)) {
      qDebug() << ToString() << " received wayward message from: " <<
        notification.GetFrom()->ToString();
      return;
    }

    ProcessData(id, notification.GetData().toHash().value("data").toByteArray());
  }

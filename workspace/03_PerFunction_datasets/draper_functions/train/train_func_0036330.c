LinkDisconnect(const Request &notification)
  {
    Id sender_id = Connections::IOverlaySender::GetRemoteId(notification.GetFrom());
    if(sender_id == Id::Zero()) {
      qWarning() << "Received a LinkDisconnect from a non-IOverlaySender." <<
        notification.GetFrom()->ToString();
      return;
    } else if(!GetGroup().Contains(sender_id)) {
      qWarning() << "Received a LinkDisconnect from a non-member:" << sender_id;
      return;
    }

    Id remote_id = Id(notification.GetData().toHash().value("remote_id").toByteArray());
    if(!GetGroup().Contains(remote_id)) {
      return;
    }

    switch(GetGroup().GetSubgroupPolicy()) {
      case Group::FixedSubgroup:
      case Group::ManagedSubgroup:

        if(!GetGroup().GetSubgroup().Contains(remote_id)) {
          HandleDisconnect(remote_id);
        }
      default:
        break;
    }
    if(GetCurrentRound()) {
      GetCurrentRound()->HandleDisconnect(remote_id);
    }
  }

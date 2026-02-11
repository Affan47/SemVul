Disconnect(Connection *con)
  {
    const Id &id = con->GetRemoteId();
    QSharedPointer<Edge> edge = con->GetEdge();

    if(_id_to_con.contains(id) && _id_to_con[id]->GetEdge() == edge) {
      _id_to_con.remove(id);
      return true;
    } else {
      qWarning() << "Connection asked to be removed by Id but not found: " << con->ToString();
      return false;
    }
  }

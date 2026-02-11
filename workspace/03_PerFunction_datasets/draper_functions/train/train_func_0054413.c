SetRemoteEdgeId(int id)
  {
    if(_remote_edge_id != -1) {
      qWarning() << "EdgeId already set.";
      return;
    }
    _remote_edge_id = id;
  }

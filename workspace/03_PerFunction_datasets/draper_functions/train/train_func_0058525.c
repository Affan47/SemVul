Remove(int connection_id) {
  ConnectionMap::iterator it = connections_.find(connection_id);
  if (it == connections_.end()) {
    ASSERT(false);
    return;
  }
  Connection* connection = it->second;
  connections_.erase(it);
  SignalConnectionClosed(this, connection_id, connection->EndProcess());
  delete connection;
  if (closing_ && connections_.empty()) {
    closing_ = false;
    SignalCloseAllComplete(this);
  }
}

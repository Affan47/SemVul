PollSocket(bool poll) {
  ASSERT(talk_base::Thread::Current() == channel_thread_);
  talk_base::CritScope cs(&crit_);


  P2PTransportChannel* p2p_channel = GetP2PChannel();
  if (p2p_channel != NULL) {
    connection_infos_.clear();
    const std::vector<Connection *> &connections = p2p_channel->connections();
    std::vector<Connection *>::const_iterator it;
    for (it = connections.begin(); it != connections.end(); it++) {
      Connection *connection = *it;
      ConnectionInfo info;
      info.best_connection = p2p_channel->best_connection() == connection;
      info.readable =
          (connection->read_state() == Connection::STATE_READABLE);
      info.writable =
          (connection->write_state() == Connection::STATE_WRITABLE);
      info.timeout =
          (connection->write_state() == Connection::STATE_WRITE_TIMEOUT);
      info.new_connection = !connection->reported();
      connection->set_reported(true);
      info.rtt = connection->rtt();
      info.sent_total_bytes = connection->sent_total_bytes();
      info.sent_bytes_second = connection->sent_bytes_second();
      info.recv_total_bytes = connection->recv_total_bytes();
      info.recv_bytes_second = connection->recv_bytes_second();
      info.local_candidate = connection->local_candidate();
      info.remote_candidate = connection->remote_candidate();
      info.key = connection;
      connection_infos_.push_back(info);
    }
  }


  monitoring_thread_->Post(this, MSG_MONITOR_SIGNAL);
  if (poll)
    channel_thread_->PostDelayed(rate_, this, MSG_MONITOR_POLL);
}

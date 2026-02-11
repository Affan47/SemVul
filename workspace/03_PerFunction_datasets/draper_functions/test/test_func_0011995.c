CreateConnections(const Candidate &remote_candidate,
                                            Port* origin_port,
                                            bool readable) {
  ASSERT(worker_thread_ == talk_base::Thread::Current());


  bool created = false;

  std::vector<Port *>::reverse_iterator it;
  for (it = ports_.rbegin(); it != ports_.rend(); ++it) {
    if (CreateConnection(*it, remote_candidate, origin_port, readable)) {
      if (*it == origin_port)
        created = true;
    }
  }

  if ((origin_port != NULL) &&
      std::find(ports_.begin(), ports_.end(), origin_port) == ports_.end()) {
    if (CreateConnection(origin_port, remote_candidate, origin_port, readable))
      created = true;
  }


  RememberRemoteCandidate(remote_candidate, origin_port);

  return created;
}

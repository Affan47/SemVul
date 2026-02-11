CompareConnections(cricket::Connection *a, cricket::Connection *b) {

  if (a->write_state() < b->write_state())
    return 1;
  if (a->write_state() > b->write_state())
    return -1;


  return CompareConnectionCandidates(a, b);
}

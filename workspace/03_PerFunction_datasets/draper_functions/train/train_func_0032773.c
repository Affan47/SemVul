OnAddressError(Port* port) {
  ASSERT(talk_base::Thread::Current() == network_thread_);
  std::vector<PortData>::iterator iter =
      std::find(ports_.begin(), ports_.end(), port);
  ASSERT(iter != ports_.end());


  if (port->type() != RELAY_PORT_TYPE)
    iter->sequence->RemoveCandidates(1);


  MaybeSignalCandidatesAllocationDone();
}

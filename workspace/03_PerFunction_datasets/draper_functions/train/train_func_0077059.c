AddAllocatedPort(Port* port,
                                                 AllocationSequence * seq,
                                                 float pref,
                                                 bool prepare_address) {
  if (!port)
    return;

  port->set_name(name_);
  port->set_preference(pref);
  port->set_generation(generation());
  if (allocator_->proxy().type != talk_base::PROXY_NONE)
    port->set_proxy(allocator_->user_agent(), allocator_->proxy());

  PortData data;
  data.port = port;
  data.sequence = seq;
  data.ready = false;
  ports_.push_back(data);

  port->SignalAddressReady.connect(this,
      &BasicPortAllocatorSession::OnAddressReady);
  port->SignalConnectionCreated.connect(this,
      &BasicPortAllocatorSession::OnConnectionCreated);
  port->SignalDestroyed.connect(this,
      &BasicPortAllocatorSession::OnPortDestroyed);
  port->SignalAddressError.connect(
      this, &BasicPortAllocatorSession::OnAddressError);
  LOG_J(LS_INFO, port) << "Added port to allocator";

  if (prepare_address)
    port->PrepareAddress();
  if (running_)
    port->Start();
}

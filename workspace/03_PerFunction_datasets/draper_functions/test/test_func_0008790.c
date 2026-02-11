Init(TransportChannel* transport_channel,
                       TransportChannel* rtcp_transport_channel) {
  if (transport_channel == NULL) {
    return false;
  }
  if (rtcp() && rtcp_transport_channel == NULL) {
    return false;
  }
  transport_channel_ = transport_channel;
  media_channel_->SetInterface(this);
  transport_channel_->SignalWritableState.connect(
      this, &BaseChannel::OnWritableState);
  transport_channel_->SignalReadPacket.connect(
      this, &BaseChannel::OnChannelRead);

  session_->SignalState.connect(this, &BaseChannel::OnSessionState);

  OnSessionState(session(), session()->state());
  set_rtcp_transport_channel(rtcp_transport_channel);
  return true;
}

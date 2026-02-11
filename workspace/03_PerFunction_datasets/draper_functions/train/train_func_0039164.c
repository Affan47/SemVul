CallChannels_w(TransportChannelFunc func) {
  ASSERT(worker_thread()->IsCurrent());
  talk_base::CritScope cs(&crit_);
  for (ChannelMap::iterator iter = channels_.begin();
       iter != channels_.end();
       ++iter) {
    ((iter->second.get())->*func)();
  }
}

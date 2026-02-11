DestroyChannel(const std::string& name) {
  ChannelMessage msg(new ChannelParams(name));
  worker_thread()->Send(this, MSG_DESTROYCHANNEL, &msg);
}

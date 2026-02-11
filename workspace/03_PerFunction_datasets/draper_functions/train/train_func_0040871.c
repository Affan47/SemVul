CreateChannel(
    const std::string& name, const std::string& content_type) {
  ChannelMessage msg(new ChannelParams(name, content_type));
  worker_thread()->Send(this, MSG_CREATECHANNEL, &msg);
  return msg.data()->channel;
}

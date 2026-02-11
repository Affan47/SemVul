OnChannelRead(TransportChannel* channel,
                                const char* data, size_t len) {

  ASSERT(worker_thread_ == talk_base::Thread::Current());


  bool rtcp = PacketIsRtcp(channel, data, len);
  talk_base::Buffer packet(data, len);
  HandlePacket(rtcp, &packet);
}

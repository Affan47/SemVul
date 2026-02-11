SendPacket(bool rtcp, talk_base::Buffer* packet) {

  if (!writable_) {
    return false;
  }


  if (talk_base::Thread::Current() != worker_thread_) {

    int message_id = (!rtcp) ? MSG_RTPPACKET : MSG_RTCPPACKET;
    PacketMessageData* data = new PacketMessageData;
    packet->TransferTo(&data->packet);
    worker_thread_->Post(this, message_id, data);
    return true;
  }


  TransportChannel* channel = (!rtcp || rtcp_mux_filter_.IsActive()) ?
      transport_channel_ : rtcp_transport_channel_;
  if (!channel || !channel->writable()) {
    return false;
  }


  if (!ValidPacket(rtcp, packet)) {
    LOG(LS_ERROR) << "Dropping outgoing " << content_name_ << " "
                  << PacketType(rtcp) << " packet: wrong size="
                  << packet->length();
    return false;
  }


  {
    talk_base::CritScope cs(&signal_send_packet_cs_);
    SignalSendPacketPreCrypto(packet->data(), packet->length(), rtcp);
  }


  if (srtp_filter_.IsActive()) {
    bool res;
    char* data = packet->data();
    int len = packet->length();
    if (!rtcp) {
      res = srtp_filter_.ProtectRtp(data, len, packet->capacity(), &len);
      if (!res) {
        int seq_num = -1;
        uint32 ssrc = 0;
        GetRtpSeqNum(data, len, &seq_num);
        GetRtpSsrc(data, len, &ssrc);
        LOG(LS_ERROR) << "Failed to protect " << content_name_
                      << " RTP packet: size=" << len
                      << ", seqnum=" << seq_num << ", SSRC=" << ssrc;
        return false;
      }
    } else {
      res = srtp_filter_.ProtectRtcp(data, len, packet->capacity(), &len);
      if (!res) {
        int type = -1;
        GetRtcpType(data, len, &type);
        LOG(LS_ERROR) << "Failed to protect " << content_name_
                      << " RTCP packet: size=" << len << ", type=" << type;
        return false;
      }
    }


    packet->SetLength(len);
  }


  {
    talk_base::CritScope cs(&signal_send_packet_cs_);
    SignalSendPacketPostCrypto(packet->data(), packet->length(), rtcp);
  }


  return (channel->SendPacket(packet->data(), packet->length())
      == static_cast<int>(packet->length()));
}

ReadPacket(RtpDumpPacket* packet) {
  if (!packet) return talk_base::SR_ERROR;

  talk_base::StreamResult res = talk_base::SR_SUCCESS;

  if (!file_header_read_) {
    res = ReadFileHeader();
    if (res != talk_base::SR_SUCCESS) {
      return res;
    }
    file_header_read_ = true;
  }


  char header[RtpDumpPacket::kHeaderLength];
  res = stream_->ReadAll(header, sizeof(header), NULL, NULL);
  if (res != talk_base::SR_SUCCESS) {
    return res;
  }
  talk_base::ByteBuffer buf(header, sizeof(header));
  uint16 dump_packet_len;
  uint16 data_len;
  buf.ReadUInt16(&dump_packet_len);
  buf.ReadUInt16(&data_len);
  packet->is_rtcp = (0 == data_len);
  buf.ReadUInt32(&packet->elapsed_time);
  packet->data.resize(dump_packet_len - sizeof(header));


  res = stream_->ReadAll(&packet->data[0], packet->data.size(), NULL, NULL);


  if (res == talk_base::SR_SUCCESS &&
      packet->IsValidRtpPacket() &&
      ssrc_buffer_.Length() == sizeof(uint32)) {
    memcpy(&packet->data[kRtpSsrcOffset], ssrc_buffer_.Data(),
           ssrc_buffer_.Length());
  }

  return res;
}

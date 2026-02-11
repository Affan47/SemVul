set_packet_filter(int filter) {
  packet_filter_ = filter;
  LOG(LS_INFO) << "RtpDumpWriter set_packet_filter to " << packet_filter_;
}

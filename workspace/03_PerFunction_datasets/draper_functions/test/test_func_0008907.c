AddRecvStream(const StreamParams& stream,
                         BaseChannel* channel,
                         std::vector<StreamParams>* recv_streams) {
  if (channel && stream.has_ssrcs()) {
    channel->AddRecvStream(stream);
  }
  recv_streams->push_back(stream);
}

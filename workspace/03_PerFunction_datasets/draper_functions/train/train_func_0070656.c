Init() {
  TransportChannel* rtcp_channel = rtcp() ?
      session()->CreateChannel(content_name(), "video_rtcp") : NULL;
  if (!BaseChannel::Init(
          session()->CreateChannel(content_name(), "video_rtp"),
          rtcp_channel)) {
    return false;
  }
  media_channel()->SignalScreencastWindowEvent.connect(
      this, &VideoChannel::OnScreencastWindowEvent);
  media_channel()->SignalMediaError.connect(
      this, &VideoChannel::OnVideoChannelError);
  srtp_filter()->SignalSrtpError.connect(
      this, &VideoChannel::OnSrtpError);
  return true;
}

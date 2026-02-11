StartMediaMonitor(int cms) {
  media_monitor_.reset(new VideoMediaMonitor(media_channel(), worker_thread(),
      talk_base::Thread::Current()));
  media_monitor_->SignalUpdate.connect(
      this, &VideoChannel::OnMediaMonitorUpdate);
  media_monitor_->Start(cms);
}

delay(void) const
{
  long int delay = 0;
  if (is_running() == true) {
    if ((oss_caps & DSP_CAP_REALTIME) == DSP_CAP_REALTIME) {
      count_info info;
      info.bytes = 0;
      if (io_mode() == io_read) {
	::ioctl(audio_fd, SNDCTL_DSP_GETIPTR, &info);
	delay = static_cast<SAMPLE_SPECS::sample_pos_t>
	  (info.bytes / frame_size()) - position_in_samples();
      }
      else {
	::ioctl(audio_fd, SNDCTL_DSP_GETOPTR, &info);
	delay = position_in_samples() -
	  static_cast<SAMPLE_SPECS::sample_pos_t>(info.bytes / frame_size());
      }
    }
    else {
      struct timeval now;
      gettimeofday(&now, NULL);
      double time = now.tv_sec * 1000000.0 + now.tv_usec -
	start_time.tv_sec * 1000000.0 - start_time.tv_usec;

      if (io_mode() == io_read)
	delay = static_cast<long int>(time * samples_per_second() / 1000000.0) - position_in_samples();
      else
	delay = position_in_samples() - static_cast<long int>(time * samples_per_second() / 1000000.0);
    }
  }
  DBC_CHECK(delay >= 0);
  return delay;
}

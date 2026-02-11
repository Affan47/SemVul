open(void) throw (AUDIO_IO::SETUP_ERROR &)
{
  ECA_LOG_MSG(ECA_LOGGER::user_objects, "open");

  double t = static_cast<double>(buffersize()) / samples_per_second();

  buffer_length_rep.tv_sec = static_cast<time_t>(floor(t));
  buffer_length_rep.tv_usec = static_cast<long>((t - buffer_length_rep.tv_sec) * 1000000.0);

  total_buffers_rep = 3;
  if (max_buffers() == true) {
    total_buffers_rep = 8;
  }
  total_buffer_length_rep.tv_sec = total_buffers_rep * buffer_length_rep.tv_sec;
  total_buffer_length_rep.tv_usec = total_buffers_rep * buffer_length_rep.tv_usec;

  AUDIO_IO_DEVICE::open();
}

set_buffersize(long int samples)
{
  if (buffersize_rep != samples ||
      static_cast<long int>(iobuf_size_rep) < buffersize_rep * frame_size()) {
    buffersize_rep = samples;
    reserve_buffer_space(buffersize_rep * frame_size());
  }
}

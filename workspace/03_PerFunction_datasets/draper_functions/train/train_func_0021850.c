read(unsigned char **buffer)
{
  if (!m_mp4 || m_track < 0) return -1;

  if (!mp4ff_read_sample_v2(m_mp4, m_track, m_sample, m_buffer))
    return -1;

  int32_t buffer_size = mp4ff_read_sample_getsize(m_mp4, m_track, m_sample);
  NeAACDecFrameInfo frame;

  m_sample++;

  *buffer = (unsigned char *)NeAACDecDecode(m_aac, &frame, m_buffer, buffer_size);
  if (frame.error) {
    debug("bad decode: %s\n", NeAACDecGetErrorMessage(frame.error));
    return 0;
  }
  return frame.samples * 2;
}

mpeg2ps_get_audio_pos(mpeg2ps_t *ps, u32 streamno)
{
  if (invalid_audio_streamno(ps, streamno)) return 0;
  return gf_f64_tell(ps->audio_streams[streamno]->m_fd);
}

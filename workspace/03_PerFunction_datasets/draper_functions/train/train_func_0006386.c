seek_position(SAMPLE_SPECS::sample_pos_t pos)
{
  if (is_open() == true) {
    fio_repp->set_file_position(pos * frame_size());
  }
  return pos;
}

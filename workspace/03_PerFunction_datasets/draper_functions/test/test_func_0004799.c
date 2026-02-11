next_riff_block(RB *t, off_t *offtmp)
{


  fio_repp->read_to_buffer(t, sizeof(RB));
  if (fio_repp->file_bytes_processed() != sizeof(RB)) {
    ECA_LOG_MSG(ECA_LOGGER::user_objects, "invalid RIFF block!");
    return false;
  }

  if (!fio_repp->is_file_ready()) return false;
  *offtmp = little_endian_uint32(t->bsize) + fio_repp->get_file_position();
  return true;
}

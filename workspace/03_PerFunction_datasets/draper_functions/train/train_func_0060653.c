write_from_buffer(void* obuf, off_t bytes) {
  if (is_file_ready() == false) {
    bytes_rep = 0;
    file_ended_rep = true;
    return;
  }

  if (fposition_rep + bytes > flength_rep)
    bytes = flength_rep - fposition_rep;

  std::memcpy(buffer_repp + fposition_rep, obuf, bytes);
  set_file_position(fposition_rep + bytes, false);
  bytes_rep = bytes;
}

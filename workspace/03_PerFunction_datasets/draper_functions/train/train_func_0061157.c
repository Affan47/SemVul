set_file_position_end(void)
{
  if (standard_mode == false) {
    int res = std::fseek(f1, 0, SEEK_END);
    if (res != 0) {
      ECA_LOG_MSG(ECA_LOGGER::info, "(eca-fileio-stream) fseek() error! (seek_end).");
    }
    else {
      curpos_rep = get_file_length();
    }
  }
}

stream_2_remove_chars(size_t nof_chars_to_remove) {
  if (stream_2 != NULL) {
    if (stream_2_wrapping_disabled == true) {
      stream_2_buffer_remove_chars(nof_chars_to_remove);
    }
    else {
      wordwrap_remove_chars(stream_2_wrapper, nof_chars_to_remove);
    }
  }
}

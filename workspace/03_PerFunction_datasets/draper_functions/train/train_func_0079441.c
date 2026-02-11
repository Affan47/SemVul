file_mode_string(umode_t st_mode) {
  static Stream *s = 0;
  if(!s)
	 s = new_stream(4);
  stream_printf(s, "%03o", st_mode & 0777);
  return reset_stream(s);
}

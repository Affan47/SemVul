scan_integer (NODE_T * p, A68_REF ref_file)
{
  A68_FILE *f = FILE_DEREF (&ref_file);
  int ch;
  reset_transput_buffer (INPUT_BUFFER);
  ch = char_scanner (f);
  while (ch != EOF_CHAR && (IS_SPACE (ch) || IS_NL_FF (ch))) {
    if (IS_NL_FF (ch)) {
      skip_nl_ff (p, &ch, ref_file);
    } else {
      ch = char_scanner (f);
    }
  }
  if (ch != EOF_CHAR && (ch == '+' || ch == '-')) {
    add_char_transput_buffer (p, INPUT_BUFFER, (char) ch);
    ch = char_scanner (f);
  }
  while (ch != EOF_CHAR && IS_DIGIT (ch)) {
    add_char_transput_buffer (p, INPUT_BUFFER, (char) ch);
    ch = char_scanner (f);
  }
  if (ch != EOF_CHAR) {
    unchar_scanner (p, f, (char) ch);
  }
}

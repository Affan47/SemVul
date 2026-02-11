put_zeroes_to_integral (NODE_T * p, int n)
{
  for (; n > 0; n--) {
    add_char_transput_buffer (p, EDIT_BUFFER, '0');
  }
}

read_integral_pattern (NODE_T * p, MOID_T * m, BYTE_T * item, A68_REF ref_file)
{
  NODE_T *q = SUB (p);
  if (q != NO_NODE && IS (q, SIGN_MOULD)) {
    int sign = 0;
    char *z;
    add_char_transput_buffer (p, INPUT_BUFFER, BLANK_CHAR);
    read_sign_mould (SUB (q), m, ref_file, &sign);
    z = get_transput_buffer (INPUT_BUFFER);
    z[0] = (char) ((sign == -1) ? '-' : '+');
    FORWARD (q);
  }
  if (q != NO_NODE && IS (q, INTEGRAL_MOULD)) {
    read_integral_mould (SUB (q), m, ref_file);
  }
  genie_string_to_value (p, m, item, ref_file);
}

genie_write_real_format (NODE_T * p, BYTE_T * item, A68_REF ref_file)
{
  if (IS (p, GENERAL_PATTERN) && NEXT_SUB (p) == NO_NODE) {
    genie_value_to_string (p, MODE (REAL), item, ATTRIBUTE (SUB (p)));
    add_string_from_stack_transput_buffer (p, FORMATTED_BUFFER);
  } else if (IS (p, GENERAL_PATTERN) && NEXT_SUB (p) != NO_NODE) {
    write_number_generic (p, MODE (REAL), item, ATTRIBUTE (SUB (p)));
  } else if (IS (p, FIXED_C_PATTERN) || IS (p, FLOAT_C_PATTERN) || IS (p, GENERAL_C_PATTERN)) {
    write_c_pattern (p, MODE (REAL), item, ref_file);
  } else if (IS (p, REAL_PATTERN)) {
    write_real_pattern (p, MODE (REAL), MODE (REAL), item, ref_file);
  } else if (IS (p, COMPLEX_PATTERN)) {
    A68_REAL im;
    STATUS (&im) = INIT_MASK;
    VALUE (&im) = 0.0;
    write_complex_pattern (p, MODE (REAL), MODE (COMPLEX), (BYTE_T *) item, (BYTE_T *) & im, ref_file);
  } else {
    pattern_error (p, MODE (REAL), ATTRIBUTE (p));
  }
}

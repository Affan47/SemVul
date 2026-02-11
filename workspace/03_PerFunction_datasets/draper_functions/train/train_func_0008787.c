C_i_check_structure_2(C_word x, C_word st, C_word loc)
{
  if(C_immediatep(x) || C_header_bits(x) != C_STRUCTURE_TYPE || C_u_i_car(x) != st) {
    error_location = loc;
    barf(C_BAD_ARGUMENT_TYPE_BAD_STRUCT_ERROR, NULL, x, st);
  }

  return C_SCHEME_UNDEFINED;
}

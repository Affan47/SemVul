C_i_check_pair_2(C_word x, C_word loc)
{
  if(C_immediatep(x) || C_block_header(x) != C_PAIR_TAG) {
    error_location = loc;
    barf(C_BAD_ARGUMENT_TYPE_NO_PAIR_ERROR, NULL, x);
  }

  return C_SCHEME_UNDEFINED;
}

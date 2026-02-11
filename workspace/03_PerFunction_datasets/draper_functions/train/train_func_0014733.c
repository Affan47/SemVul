C_i_foreign_struct_wrapper_argumentp(C_word t, C_word x)
{
  if(C_immediatep(x) || C_header_bits(x) != C_STRUCTURE_TYPE || C_block_item(x, 0) != t)
    barf(C_BAD_ARGUMENT_TYPE_BAD_STRUCT_ERROR, NULL, t, x);

  return x;
}

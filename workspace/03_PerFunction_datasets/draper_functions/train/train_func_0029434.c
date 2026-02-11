C_enumerate_symbols(C_SYMBOL_TABLE *stable, C_word pos)
{
  int i;
  C_word
    sym,
    bucket = C_u_i_car(pos);

  if(!C_truep(bucket)) return C_SCHEME_FALSE;
  else i = C_unfix(bucket);

  bucket = C_u_i_cdr(pos);

  while(bucket == C_SCHEME_END_OF_LIST) {
    if(++i >= stable->size) {
      C_set_block_item(pos, 0, C_SCHEME_FALSE);
      return C_SCHEME_FALSE;
    }
    else bucket = stable->table[ i ];
  }

  sym = C_u_i_car(bucket);
  C_set_block_item(pos, 0, C_fix(i));
  C_mutate(&C_u_i_cdr(pos), C_u_i_cdr(bucket));
  return sym;
}

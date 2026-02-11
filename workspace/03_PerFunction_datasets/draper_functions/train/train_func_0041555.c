C_zap_strings(C_word str)
{
  int i;

  for(i = 0; i < symbol_table->size; ++i) {
    C_word bucket, sym;

    for(bucket = symbol_table->table[ i ];
        bucket != C_SCHEME_END_OF_LIST;
        bucket = C_u_i_cdr(bucket)) {
      sym = C_u_i_car(bucket);
      C_set_block_item(sym, 1, str);
    }
  }
}

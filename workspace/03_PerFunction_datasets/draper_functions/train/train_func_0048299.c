C_i_assv(C_word x, C_word lst)
{
  C_word a;

  while(!C_immediatep(lst) && C_block_header(lst) == C_PAIR_TAG) {
    a = C_u_i_car(lst);

    if(!C_immediatep(a) && C_block_header(a) == C_PAIR_TAG) {
      if(C_truep(C_i_eqvp(C_u_i_car(a), x))) return a;
    }
    else barf(C_BAD_ARGUMENT_TYPE_ERROR, "assv", a);

    lst = C_u_i_cdr(lst);
  }

  return C_SCHEME_FALSE;
}

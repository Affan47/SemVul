sb_ivy_write_term(String_buf sb, Term t)
{
  if (VARIABLE(t)) {
    sb_append(sb, "v");
    sb_append_int(sb, VARNUM(t));
  }
  else {
    int i;
    sb_append(sb, "(");
    sb_append(sb, sn_to_str(SYMNUM(t)));
    for (i = 0; i < ARITY(t); i++) {
      sb_append(sb, " ");
      sb_ivy_write_term(sb, ARG(t,i));
    }
    sb_append(sb, ")");
  }
}

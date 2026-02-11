make_undef (str, op)
     char *str;
     FILE_BUF *op;
{
  FILE_BUF *ip;
  struct directive *kt;

  ip = &instack[++indepth];
  ip->nominal_fname = ip->fname = "*undef*";
  ip->nominal_fname_len = strlen (ip->nominal_fname);

  ip->buf = ip->bufp = (U_CHAR *) str;
  ip->length = strlen (str);
  ip->lineno = 1;
  ip->macro = 0;
  ip->free_ptr = 0;
  ip->if_stack = if_stack;
  ip->system_header_p = 0;

  for (kt = directive_table; kt->type != T_UNDEF; kt++)
    ;

  do_undef ((U_CHAR *) str, (U_CHAR *) str + strlen (str), op, kt);
  --indepth;
}

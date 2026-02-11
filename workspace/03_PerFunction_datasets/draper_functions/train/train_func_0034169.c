print_fsym_precedence(FILE *fp)
{
  Ilist fsyms = current_fsym_precedence();
  Ilist p;

  printf("Function symbol precedence:  function_order([");
  for (p = fsyms; p; p = p->next)
    printf(" %s%s", sn_to_str(p->i), p->next ? "," : "");
  printf(" ]).\n");

  zap_ilist(fsyms);
}

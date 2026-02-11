dollar_out(struct term *t)
{
  struct term *t1;

  if (proper_list(t)) {
    printf("\n");
    for (t1 = t; t1->sym_num != Nil_sym_num; t1 = t1->farg->narg->argval) {
      if (t != t1)
	printf(" ");
      dollar_out_non_list(t1->farg->argval);
    }
    printf(".\n\n");
  }
  else
    dollar_out_non_list(t);
}

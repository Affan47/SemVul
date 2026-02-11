compare_array_operand(Operand *opt1,
		      Operand *opt2,
		      int     idx_entry)
{
  int i;

  if (opt1->nsub != opt2->nsub) {
      return 0;
  }
  for (i = 0; i < opt1->nsub; i++) {
    if (!(compare_array_sub_script(opt1->sub[i],
				   opt2->sub[i],
				   idx_entry))) {
      return 0;
    }
  }

  return 1;
}

process_define_predicate (rtx desc)
{
  struct pred_data *pred = XCNEW (struct pred_data);
  char codes[NUM_RTX_CODE];
  int i;

  pred->name = XSTR (desc, 0);
  if (GET_CODE (desc) == DEFINE_SPECIAL_PREDICATE)
    pred->special = 1;

  compute_predicate_codes (XEXP (desc, 1), codes);

  for (i = 0; i < NUM_RTX_CODE; i++)
    if (codes[i] != N)
      add_predicate_code (pred, (enum rtx_code) i);

  add_predicate (pred);
}

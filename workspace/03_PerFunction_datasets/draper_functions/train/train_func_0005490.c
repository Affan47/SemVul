add_condition (struct inline_summary *summary, int operand_num,
	       enum tree_code code, tree val)
{
  int i;
  struct condition *c;
  struct condition new_cond;

  for (i = 0; VEC_iterate (condition, summary->conds, i, c); i++)
    {
      if (c->operand_num == operand_num
	  && c->code == code
	  && c->val == val)
        return single_cond_predicate (i + predicate_first_dynamic_condition);
    }

  if (i == NUM_CONDITIONS - predicate_first_dynamic_condition)
    return true_predicate ();

  new_cond.operand_num = operand_num;
  new_cond.code = code;
  new_cond.val = val;
  VEC_safe_push (condition, gc, summary->conds, &new_cond);
  return single_cond_predicate (i + predicate_first_dynamic_condition);
}

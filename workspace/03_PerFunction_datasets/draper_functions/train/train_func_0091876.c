eval_limit_ok(Interp p, int number_of_vars)
{
  if (Eval_limit == -1)
    return TRUE;
  else {
    int evals_required = int_power(interp_size(p), number_of_vars);
    return evals_required <= Eval_limit;
  }
}

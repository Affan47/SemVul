Fct_Fast_Div(WamWord x, WamWord y)
{
  long vx = UnTag_INT(x);
  long vy = UnTag_INT(y);

  if (vy == 0)
    Pl_Err_Evaluation(evluation_zero_divisor);

  return Tag_INT(vx / vy);
}

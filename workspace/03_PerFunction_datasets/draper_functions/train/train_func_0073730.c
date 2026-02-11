autohelperendpat81(int trans, int move, int color, int action)
{
  int a;
  UNUSED(color);
  UNUSED(action);

  a = AFFINE_TRANSFORM(683, trans, move);

  return is_marginal_eye_space(move) && is_proper_eye_space(a) && max_eye_value(a)>0;
}

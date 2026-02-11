autohelperconn34(int trans, int move, int color, int action)
{
  int a, b, c, d;
  UNUSED(color);
  UNUSED(action);

  a = AFFINE_TRANSFORM(611, trans, move);
  b = AFFINE_TRANSFORM(647, trans, move);
  c = AFFINE_TRANSFORM(648, trans, move);
  d = AFFINE_TRANSFORM(610, trans, move);

  return ATTACK_MACRO(a) && ATTACK_MACRO(b) && !cut_possible(c, OTHER_COLOR(color)) && !cut_possible(d, OTHER_COLOR(color));
}

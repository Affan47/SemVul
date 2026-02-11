autohelperowl_defendpat322(int trans, int move, int color, int action)
{
  int a, c, d, B;
  UNUSED(color);
  UNUSED(action);

  a = AFFINE_TRANSFORM(721, trans, move);
  c = AFFINE_TRANSFORM(611, trans, move);
  d = AFFINE_TRANSFORM(649, trans, move);
  B = AFFINE_TRANSFORM(683, trans, move);

  return countlib(B)<=4 && owl_escape_value(c) + owl_escape_value(d) > 0&& play_attack_defend2_n(color, 1, 2, move, a, a, B);
}

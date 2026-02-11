autohelperowl_defendpat385(int trans, int move, int color, int action)
{
  int a, b, d, C;
  UNUSED(color);
  UNUSED(action);

  a = AFFINE_TRANSFORM(721, trans, move);
  b = AFFINE_TRANSFORM(722, trans, move);
  d = AFFINE_TRANSFORM(758, trans, move);
  C = AFFINE_TRANSFORM(685, trans, move);

  return owl_escape_value(d)>0 && !play_attack_defend2_n(color, 0, 3, move, a, b, a, C);
}

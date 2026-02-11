autohelperowl_attackpat226(int trans, int move, int color, int action)
{
  int a, b, c;
  UNUSED(color);
  UNUSED(action);

  a = AFFINE_TRANSFORM(683, trans, move);
  b = AFFINE_TRANSFORM(685, trans, move);
  c = AFFINE_TRANSFORM(721, trans, move);

  return (owl_escape_value(a)>0 || owl_escape_value(b)>0) && play_attack_defend_n(color, 1, 2, move, c, c);
}

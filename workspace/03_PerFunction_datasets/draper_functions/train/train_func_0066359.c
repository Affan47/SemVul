autohelperowl_attackpat18(int trans, int move, int color, int action)
{
  int a, b, c;
  UNUSED(color);
  UNUSED(action);

  a = AFFINE_TRANSFORM(683, trans, move);
  b = AFFINE_TRANSFORM(682, trans, move);
  c = AFFINE_TRANSFORM(756, trans, move);

  return  play_attack_defend_n(color, 1, 2, move, a, a) || !play_attack_defend_n(color, 1, 4, move, a, b, c, move);
}

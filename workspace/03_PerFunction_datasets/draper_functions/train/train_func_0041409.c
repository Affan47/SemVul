autohelperbarrierspat7(int trans, int move, int color, int action)
{
  int a, b, c, d;
  UNUSED(color);
  UNUSED(action);

  a = AFFINE_TRANSFORM(648, trans, move);
  b = AFFINE_TRANSFORM(611, trans, move);
  c = AFFINE_TRANSFORM(610, trans, move);
  d = AFFINE_TRANSFORM(647, trans, move);

  return play_attack_defend2_n(color, 1, 3, a, b, c, a, c) || !play_attack_defend2_n(color, 1, 2, a, b, b, d);
}

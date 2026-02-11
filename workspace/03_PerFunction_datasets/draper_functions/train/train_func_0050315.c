autohelperbarrierspat23(int trans, int move, int color, int action)
{
  int a, b, c, d, e;
  UNUSED(color);
  UNUSED(action);

  a = AFFINE_TRANSFORM(758, trans, move);
  b = AFFINE_TRANSFORM(721, trans, move);
  c = AFFINE_TRANSFORM(722, trans, move);
  d = AFFINE_TRANSFORM(759, trans, move);
  e = AFFINE_TRANSFORM(795, trans, move);

  return !play_attack_defend2_n(color, 1, 3, a, b, c, a, c) || !play_attack_defend2_n(color, 1, 3, b, a, d, d, e);
}

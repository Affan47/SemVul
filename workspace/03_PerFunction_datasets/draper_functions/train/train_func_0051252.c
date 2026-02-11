autohelperendpat0(int trans, int move, int color, int action)
{
  int a, b, c;
  UNUSED(color);
  UNUSED(action);

  a = AFFINE_TRANSFORM(647, trans, move);
  b = AFFINE_TRANSFORM(610, trans, move);
  c = AFFINE_TRANSFORM(646, trans, move);

  return is_marginal_eye_space(move) && is_proper_eye_space(a) && is_proper_eye_space(b) && !play_attack_defend_n(OTHER_COLOR(color), 1, 1, move, c);
}

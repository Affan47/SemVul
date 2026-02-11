autohelperendpat3(int trans, int move, int color, int action)
{
  int a, b, c, d;
  UNUSED(color);
  UNUSED(action);

  a = AFFINE_TRANSFORM(759, trans, move);
  b = AFFINE_TRANSFORM(722, trans, move);
  c = AFFINE_TRANSFORM(685, trans, move);
  d = AFFINE_TRANSFORM(721, trans, move);

  return is_marginal_eye_space(a) && is_proper_eye_space(b) && is_proper_eye_space(c) && play_attack_defend_n(OTHER_COLOR(color), 1, 1, a, d);
}

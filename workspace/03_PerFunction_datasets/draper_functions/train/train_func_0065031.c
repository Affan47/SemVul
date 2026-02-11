autohelperendpat80(int trans, int move, int color, int action)
{
  int a, b;
  UNUSED(color);
  UNUSED(action);

  a = AFFINE_TRANSFORM(685, trans, move);
  b = AFFINE_TRANSFORM(683, trans, move);

  return is_marginal_eye_space(move) && is_proper_eye_space(b) && max_eye_value(b)>0 && play_attack_defend_n(color, 1, 2, move, a, a);
}

autohelperowl_defendpat168(int trans, int move, int color, int action)
{
  int a, b, C;
  UNUSED(color);
  UNUSED(action);

  a = AFFINE_TRANSFORM(648, trans, move);
  b = AFFINE_TRANSFORM(685, trans, move);
  C = AFFINE_TRANSFORM(721, trans, move);

  return !obvious_false_eye(a, color)&& play_attack_defend_n(color, 1, 2, move, b, C) && !ATTACK_MACRO(C);
}

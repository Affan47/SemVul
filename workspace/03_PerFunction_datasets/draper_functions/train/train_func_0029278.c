autohelperowl_defendpat124(int trans, int move, int color, int action)
{
  int a, b;
  UNUSED(color);
  UNUSED(action);

  a = AFFINE_TRANSFORM(683, trans, move);
  b = AFFINE_TRANSFORM(685, trans, move);

  return play_attack_defend_n(color, 1, 2, move, a, a) && play_attack_defend_n(color, 1, 2, move, b, b);
}

autohelperowl_defendpat273(int trans, int move, int color, int action)
{
  int a, b, c, D;
  UNUSED(color);
  UNUSED(action);

  a = AFFINE_TRANSFORM(685, trans, move);
  b = AFFINE_TRANSFORM(686, trans, move);
  c = AFFINE_TRANSFORM(649, trans, move);
  D = AFFINE_TRANSFORM(722, trans, move);

  return (countlib(b)>1 && play_attack_defend_n(color, 1, 2, move, a, a) && !play_attack_defend2_n(OTHER_COLOR(color), 1, 3, move, NO_MOVE, a, a, c))&& (!somewhere(OTHER_COLOR(color), 0, 1, D) || play_attack_defend_n(color, 1, 2, move, a, D))&& (!is_legal(D, OTHER_COLOR(color)) || play_attack_defend_n(color, 1, 2, move, D, D));
}

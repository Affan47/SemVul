autohelperbarrierspat84(int trans, int move, int color, int action)
{
  int a, b, d, C;
  UNUSED(color);

  a = AFFINE_TRANSFORM(648, trans, move);
  b = AFFINE_TRANSFORM(611, trans, move);
  d = AFFINE_TRANSFORM(647, trans, move);
  C = AFFINE_TRANSFORM(685, trans, move);

  if (!action)
    return play_attack_defend_n(color, 1, 2, a, b, C);
  return (!play_attack_defend_n(OTHER_COLOR(color), 1, 1, a, d));;

  return 0;
}

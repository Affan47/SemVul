autohelperbarrierspat88(int trans, int move, int color, int action)
{
  int a, b, c, C;
  UNUSED(color);

  a = AFFINE_TRANSFORM(722, trans, move);
  b = AFFINE_TRANSFORM(685, trans, move);
  c = AFFINE_TRANSFORM(684, trans, move);
  C = AFFINE_TRANSFORM(721, trans, move);

  if (!action)
    return play_attack_defend2_n(color, 1, 2, a, b, C, b);;
  return (!play_attack_defend_n(OTHER_COLOR(color), 1, 1, b, c));;

  return 0;
}

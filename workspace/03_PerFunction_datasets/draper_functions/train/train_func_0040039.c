autohelperbarrierspat188(int trans, int move, int color, int action)
{
  int a, b, c, d;
  UNUSED(color);

  a = AFFINE_TRANSFORM(648, trans, move);
  b = AFFINE_TRANSFORM(685, trans, move);
  c = AFFINE_TRANSFORM(722, trans, move);
  d = AFFINE_TRANSFORM(758, trans, move);

  if (!action)
    return play_attack_defend_n(color, 1, 2, a, b, b) && play_attack_defend_n(color, 1, 3, a, c, b, c);
  influence_mark_non_territory(c, OTHER_COLOR(color));influence_mark_non_territory(d, OTHER_COLOR(color));;

  return 0;
}

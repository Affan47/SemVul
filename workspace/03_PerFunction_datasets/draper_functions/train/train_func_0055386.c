autohelperbarrierspat203(int trans, int move, int color, int action)
{
  int a, b, c, d, e, f;
  UNUSED(color);

  a = AFFINE_TRANSFORM(574, trans, move);
  b = AFFINE_TRANSFORM(611, trans, move);
  c = AFFINE_TRANSFORM(575, trans, move);
  d = AFFINE_TRANSFORM(576, trans, move);
  e = AFFINE_TRANSFORM(612, trans, move);
  f = AFFINE_TRANSFORM(649, trans, move);

  if (!action)
    return play_attack_defend_n(color, 0, 6, a, b, c, d, e, f, a);
  influence_mark_non_territory(b, OTHER_COLOR(color));influence_mark_non_territory(c, OTHER_COLOR(color));influence_mark_non_territory(d, OTHER_COLOR(color));influence_mark_non_territory(e, OTHER_COLOR(color));influence_mark_non_territory(f, OTHER_COLOR(color));;

  return 0;
}

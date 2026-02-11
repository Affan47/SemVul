autohelperbarrierspat214(int trans, int move, int color, int action)
{
  int a, b, c, d, e;
  UNUSED(color);

  a = AFFINE_TRANSFORM(575, trans, move);
  b = AFFINE_TRANSFORM(537, trans, move);
  c = AFFINE_TRANSFORM(612, trans, move);
  d = AFFINE_TRANSFORM(538, trans, move);
  e = AFFINE_TRANSFORM(573, trans, move);

  if (!action)
    return safe_move(a, color) && play_attack_defend_n(color, 1, 4, a, b, c, d, b);
  influence_mark_non_territory(e, OTHER_COLOR(color));;

  return 0;
}

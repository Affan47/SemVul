autohelperfusekipat161(int trans, int move, int color, int action)
{
  int a, b, c, d, e, f, g, h;
  UNUSED(color);

  a = AFFINE_TRANSFORM(724, trans, move);
  b = AFFINE_TRANSFORM(761, trans, move);
  c = AFFINE_TRANSFORM(798, trans, move);
  d = AFFINE_TRANSFORM(835, trans, move);
  e = AFFINE_TRANSFORM(725, trans, move);
  f = AFFINE_TRANSFORM(762, trans, move);
  g = AFFINE_TRANSFORM(799, trans, move);
  h = AFFINE_TRANSFORM(836, trans, move);

  if (!action)
    return  somewhere(OTHER_COLOR(color), 1, 8, a, b, c, d, e, f, g, h);
   add_replacement_move(c, move, color); add_replacement_move(d, move, color);

  return 0;
}

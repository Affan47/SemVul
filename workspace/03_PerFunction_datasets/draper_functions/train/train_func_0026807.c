autohelperowl_attackpat258(int trans, int move, int color, int action)
{
  int a, b, c;
  UNUSED(color);
  UNUSED(action);

  a = AFFINE_TRANSFORM(646, trans, move);
  b = AFFINE_TRANSFORM(609, trans, move);
  c = AFFINE_TRANSFORM(720, trans, move);

  return  somewhere(color, 0, 2, a, b) && ATTACK_MACRO(c);
}

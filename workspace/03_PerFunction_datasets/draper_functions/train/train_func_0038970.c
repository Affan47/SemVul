autohelperowl_defendpat487(int trans, int move, int color, int action)
{
  int a, B;
  UNUSED(color);
  UNUSED(action);

  a = AFFINE_TRANSFORM(609, trans, move);
  B = AFFINE_TRANSFORM(682, trans, move);

  return  owl_proper_eye(a) && !ATTACK_MACRO(B);
}

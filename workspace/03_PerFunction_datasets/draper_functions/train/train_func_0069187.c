autohelperendpat97(int trans, int move, int color, int action)
{
  int a, b;
  UNUSED(color);
  UNUSED(action);

  a = AFFINE_TRANSFORM(648, trans, move);
  b = AFFINE_TRANSFORM(721, trans, move);

  return is_halfeye(half_eye,a) && max_eye_value(a)>0 && !false_eye_territory[a] && !dragon_weak(b);
}

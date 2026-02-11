autohelperowl_attackpat163(int trans, int move, int color, int action)
{
  int a, b, A;
  UNUSED(color);
  UNUSED(action);

  a = AFFINE_TRANSFORM(721, trans, move);
  b = AFFINE_TRANSFORM(759, trans, move);
  A = AFFINE_TRANSFORM(722, trans, move);

  return  (owl_topological_eye(a, board[A])<=2) && (owl_topological_eye(b, board[A])==2);
}

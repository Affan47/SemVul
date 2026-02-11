autohelperowl_defendpat175(int trans, int move, int color, int action)
{
  int a, b, B;
  UNUSED(color);
  UNUSED(action);

  a = AFFINE_TRANSFORM(720, trans, move);
  b = AFFINE_TRANSFORM(722, trans, move);
  B = AFFINE_TRANSFORM(685, trans, move);

  return  (owl_topological_eye(a, board[B])==2) && ((owl_topological_eye(b, board[B])==2) || (owl_topological_eye(b, board[B])==3));
}

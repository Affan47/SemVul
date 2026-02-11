get_move_from_stack(int k, int *move, int *color)
{
  gg_assert(k < stackp);
  *move = stack[k];
  *color = move_color[k];
}

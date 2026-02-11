min_max_extent (FttCell * cell, ClosestGrid * g)
{
  FttVector pos;

  ftt_cell_pos (cell, &pos);
  if (pos.x > g->max.x) g->max.x = pos.x;
  if (pos.y > g->max.y) g->max.y = pos.y;
  if (pos.x < g->min.x) g->min.x = pos.x;
  if (pos.y < g->min.y) g->min.y = pos.y;
}

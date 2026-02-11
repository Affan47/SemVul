draw_curves(Graph g)
{
  Curve c;

  gsave();
  printf("\n");
  if (g->clip) set_clip(g);
  for(c = first(g->curves); c != nil(g->curves); c = next(c)) {
    draw_curve(c, g);
  }
  grestore();
  printf("\n");
}

draw_graph(Graph g)
{
  comment("Drawing New Graph");
  printf("%f %f translate\n", g->x_translate, g->y_translate);
  if (g->border) {
    printline(0.0, 0.0, 0.0, g->y_axis->psize, 'x');
    printline(0.0, 0.0, 0.0, g->x_axis->psize, 'y');
    printline(g->x_axis->psize, 0.0, g->x_axis->psize, g->y_axis->psize, 'x');
    printline(g->y_axis->psize, 0.0, g->y_axis->psize, g->x_axis->psize, 'y');
  }
  draw_axis(g->x_axis, g->y_axis);
  draw_axis(g->y_axis, g->x_axis);
  draw_label(g->title);
  draw_curves(g);
  draw_legend(g);
  draw_strings(g);
  printf("%f %f translate\n", - g->x_translate, - g->y_translate);

}

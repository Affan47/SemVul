process_title(Graph g)
{

  float ytitleloc;

  if (g->title->x == FSIG) g->title->x = g->x_axis->psize / 2.0;
    else g->title->x = ctop(g->title->x, g->x_axis);
  if (g->title->y != FSIG) g->title->y = ctop(g->title->y, g->y_axis);
  else {
    ytitleloc = 0.0;
    if (g->x_axis->draw_axis_label && g->x_axis->label->label != CNULL)
      ytitleloc = MIN(ytitleloc, g->x_axis->label->ymin);
    if (g->x_axis->draw_hash_labels)
      ytitleloc = MIN(ytitleloc, g->x_axis->hl->ymin);
    if (g->x_axis->draw_hash_marks)
      ytitleloc = MIN(ytitleloc, g->x_axis->draw_hash_marks_at - HASH_SIZE);
    if (g->legend->type == 'u')
      ytitleloc = MIN(ytitleloc, g->legend->l->ymin);

    g->title->y = ytitleloc - 10.0;
  }
  process_label(g->title, g, 0);
}

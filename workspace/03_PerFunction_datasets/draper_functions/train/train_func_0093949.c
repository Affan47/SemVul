movepts_history_contains (gint i, gint j, GGobiData * d, ggobid * gg)
{

  if (g_slist_length (d->movepts_history) > 0) {
    GSList *l;
    celld *cell;
    for (l = d->movepts_history; l; l = l->next) {
      cell = (celld *) l->data;
      if (cell->i == i && cell->j == j) {
        return true;
      }
    }
  }

  return false;
}

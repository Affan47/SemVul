maxlevel (FttCell * cell, GfsSimulation * sim)
{
  GSList * i = sim->adapts->items;
  guint maxlevel = G_MAXINT;

  while (i) {
    GfsAdapt * a = i->data;
    guint l;

    if (a->active && (l = gfs_function_value (a->maxlevel, cell)) < maxlevel)
      maxlevel = l;
    i = i->next;
  }
  return maxlevel;
}

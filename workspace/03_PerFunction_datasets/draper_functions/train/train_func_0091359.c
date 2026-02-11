edgeset_add (displayd * display)
{
  GGobiData *d;
  GGobiData *e;
  gint k;
  gboolean added = false;
  ggobid *gg;
  if (!display)
    return (false);

  d = display->d;
  gg = GGobiFromDisplay (display);

  if (gg->d != NULL) {
    gint nd = g_slist_length (gg->d);

    if (d->idTable) {
      for (k = 0; k < nd; k++) {
        e = (GGobiData *) g_slist_nth_data (gg->d, k);
        if (  e->edge.n > 0) {
          setDisplayEdge (display, e);
          added = true;
          break;
        }
      }
    }
  }

  return added;
}

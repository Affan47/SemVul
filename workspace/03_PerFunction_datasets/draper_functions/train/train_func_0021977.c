plotted (displayd * display, gint * cols, gint ncols, GGobiData * d)
{
  GList *l;
  splotd *sp;
  gint j;
  for (l = display->splots; l; l = l->next) {
    sp = (splotd *) l->data;

    for (j = 0; j < ncols; j++) {
      if (sp->xyvars.x == cols[j]) {
        return (sp->xyvars.x);
      }
    }
  }
  return (-1);
}

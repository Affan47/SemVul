ntext_mup(GtkWidget *widget, GdkEventButton *eb,
		   gpointer data)
{
  NText *me = (NText *) data;
  TPoint c;
  bool   dirty = false;

  if (!eb) return FALSE;

  if (eb->button == 1) {
    if (!me->havesel) return FALSE;
    if (me->dropmup) {
      me->dropmup--;
      return FALSE;
    }
    if (me->calcTP(c, (int) (eb->x), (int) (eb->y))) {
      me->B = c;
      dirty = true;
    }
    if (me->A == me->B) {
      me->havesel = false;
      dirty = true;
    }
    if (dirty)
      me->repaint();
    if (me->havesel)
      gtk_selection_owner_set(me->body, GDK_SELECTION_PRIMARY,eb->time);
  }
  return TRUE;
}

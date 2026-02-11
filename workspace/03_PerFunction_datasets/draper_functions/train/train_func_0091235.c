editor_arrow_right_clicked(GtkWidget *widget, editor_t *e)
{
  g_assert(e != NULL);

  e->x++;
  editor_refresh(e);
}

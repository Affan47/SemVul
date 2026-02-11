x_event_hschanged (GtkAdjustment *adj, GSCHEM_TOPLEVEL *w_current)
{
  TOPLEVEL *toplevel = w_current->toplevel;
  int current_left;
  int new_left;
  GtkAdjustment        *hadjustment;

  g_return_if_fail (w_current != NULL);

  if (w_current->scrollbars_flag == FALSE) {
    return;
  }

  hadjustment =
  gtk_range_get_adjustment(GTK_RANGE(w_current->h_scrollbar));

  current_left = toplevel->page_current->left;
  new_left = (int) hadjustment->value;

  toplevel->page_current->left = new_left;
  toplevel->page_current->right =
    toplevel->page_current->right -
    (current_left - new_left);

  o_invalidate_all (w_current);
}

arrangement_cb (GtkWidget * w, ggobid * gg)
{
  gint indx = gtk_combo_box_get_active (GTK_COMBO_BOX (w));

  if (indx != gg->current_display->cpanel.parcoords_arrangement)
    parcoords_reset_arrangement (gg->current_display, indx, gg);

  gg->current_display->cpanel.parcoords_arrangement = indx;
}

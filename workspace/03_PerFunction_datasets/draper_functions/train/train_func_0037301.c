simo_combo_box_arrow_down_cb(GtkWidget      *widget,
                             GdkEventButton *event,
                             gpointer        data)
{
  SimoComboBox *combo_box = (SimoComboBox *) data;

  if (event->button != 1) {
    return FALSE;
  }

  if (combo_box->priv->n_lines == 1) {
    return TRUE;
  }

  simo_combo_box_set_n_lines(combo_box, combo_box->priv->n_lines - 1);
  if (combo_box->priv->n_lines == 1) {
    gtk_widget_grab_focus(combo_box->entry);
  }

  return TRUE;
}

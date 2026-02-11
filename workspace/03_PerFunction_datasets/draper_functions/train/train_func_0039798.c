cluster_free (gint k, GGobiData * d, ggobid * gg)
{
  if (d->clusvui[k].da) {
    gtk_widget_destroy (d->clusvui[k].da);
    gtk_widget_destroy (d->clusvui[k].h_btn);
    gtk_widget_destroy (d->clusvui[k].nh_lbl);
    gtk_widget_destroy (d->clusvui[k].ns_lbl);
    gtk_widget_destroy (d->clusvui[k].n_lbl);
  }
}

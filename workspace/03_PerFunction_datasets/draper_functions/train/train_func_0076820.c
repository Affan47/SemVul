frogr_main_view_pulse_progress (FrogrMainView *self)
{
  FrogrMainViewPrivate *priv = NULL;

  g_return_if_fail(FROGR_IS_MAIN_VIEW (self));

  priv = FROGR_MAIN_VIEW_GET_PRIVATE (self);


  gtk_progress_bar_pulse (GTK_PROGRESS_BAR (priv->progress_bar));


  gtk_progress_bar_set_show_text (GTK_PROGRESS_BAR (priv->progress_bar), FALSE);
}

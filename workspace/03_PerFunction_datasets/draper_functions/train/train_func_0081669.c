zoom_options_set_parent (ZoomOptions *self,
			 GtkWindow   *parent)
{
  g_return_if_fail (ZOOM_IS_OPTIONS (self));

  gtk_window_set_transient_for (GTK_WINDOW (self->priv->dialog), parent);
  gtk_window_set_modal (GTK_WINDOW (self->priv->dialog), TRUE);
  gtk_widget_show (self->priv->dialog);
}

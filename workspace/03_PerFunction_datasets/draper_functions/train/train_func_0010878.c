egg_list_box_set_adjustment (EggListBox *list_box,
			     GtkAdjustment *adjustment)
{
  EggListBoxPrivate *priv = list_box->priv;

  g_return_if_fail (list_box != NULL);

  g_object_ref (adjustment);
  if (priv->adjustment)
    g_object_unref (priv->adjustment);
  priv->adjustment = adjustment;
  gtk_container_set_focus_vadjustment (GTK_CONTAINER (list_box),
				       adjustment);
}

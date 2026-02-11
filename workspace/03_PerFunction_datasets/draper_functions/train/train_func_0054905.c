goa_spinner_button_constructed (GObject *object)
{
  GoaSpinnerButton *self = GOA_SPINNER_BUTTON (object);
  GoaSpinnerButtonPrivate *priv = self->priv;
  GtkStockItem item;

  G_OBJECT_CLASS (goa_spinner_button_parent_class)->constructed (object);

  if (priv->use_stock && gtk_stock_lookup (priv->text, &item))
    priv->label = gtk_label_new_with_mnemonic (item.label);
  else
    priv->label = gtk_label_new_with_mnemonic (priv->text);

  gtk_widget_set_hexpand (priv->label, TRUE);
  gtk_widget_set_halign (priv->label, GTK_ALIGN_CENTER);

  gtk_label_set_mnemonic_widget (GTK_LABEL (priv->label), GTK_WIDGET (self));
  gtk_container_add (GTK_CONTAINER (priv->grid), priv->label);
}

account_widget_entry_changed_cb (GtkEditable *entry,
    TpawAccountWidget *self)
{
  if (self->priv->automatic_change)
    return;

  account_widget_entry_changed_common (self, GTK_ENTRY (entry), FALSE);
  tpaw_account_widget_changed (self);
}

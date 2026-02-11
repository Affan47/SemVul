reload_contact_info (TpawUserInfo *self)
{
  TpConnection *connection;
  TpContact *contact = NULL;
  TpContactInfoFlags flags;


  if (self->priv->details_cancellable != NULL)
    g_cancellable_cancel (self->priv->details_cancellable);
  g_clear_object (&self->priv->details_cancellable);


  gtk_container_foreach (GTK_CONTAINER (self), grid_foreach_cb, NULL);
  gtk_widget_hide (self->priv->details_label);
  gtk_widget_hide (self->priv->details_spinner);

  tp_clear_pointer (&self->priv->details_to_set, tp_contact_info_list_free);
  self->priv->details_changed = FALSE;

  connection = tp_account_get_connection (self->priv->account);
  if (connection != NULL)
    {
      contact = tp_connection_get_self_contact (connection);

      if (!tp_proxy_is_prepared (connection,
            TP_CONNECTION_FEATURE_CONTACT_INFO))
        {
          GQuark features[] = { TP_CONNECTION_FEATURE_CONTACT_INFO, 0 };
          tp_proxy_prepare_async (connection, features,
              connection_contact_info_prepared_cb, g_object_ref (self));
        }
    }


  if (contact == NULL)
    {
      GtkWidget *infobar;
      GtkWidget *content;
      GtkWidget *label;

      infobar = gtk_info_bar_new ();
      gtk_info_bar_set_message_type (GTK_INFO_BAR (infobar), GTK_MESSAGE_INFO);
      content = gtk_info_bar_get_content_area (GTK_INFO_BAR (infobar));
      label = gtk_label_new (_("Go online to edit your personal information."));
      gtk_container_add (GTK_CONTAINER (content), label);
      gtk_widget_show (label);

      gtk_grid_attach_next_to ((GtkGrid *) self, infobar,
          NULL, GTK_POS_BOTTOM, 3, 1);
      gtk_widget_show (infobar);

      g_object_set_data (G_OBJECT (infobar),
          DATA_IS_CONTACT_INFO, (gpointer) TRUE);
      return;
    }

  if (!tp_proxy_has_interface_by_id (connection,
          TP_IFACE_QUARK_CONNECTION_INTERFACE_CONTACT_INFO))
    return;

  flags = tp_connection_get_contact_info_flags (connection);
  if ((flags & TP_CONTACT_INFO_FLAG_CAN_SET) == 0)
    return;


  gtk_widget_show (self->priv->details_spinner);
  gtk_spinner_start (GTK_SPINNER (self->priv->details_spinner));

  g_assert (self->priv->details_cancellable == NULL);
  self->priv->details_cancellable = g_cancellable_new ();
  tp_contact_request_contact_info_async (contact,
      self->priv->details_cancellable, request_contact_info_cb,
      self);
}

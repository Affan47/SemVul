photos_dlna_renderers_dialog_init (PhotosDlnaRenderersDialog *self)
{
  PhotosDlnaRenderersDialogPrivate *priv;
  GList *renderers;

  self->priv = G_TYPE_INSTANCE_GET_PRIVATE (self,
                                            PHOTOS_TYPE_DLNA_RENDERERS_DIALOG,
                                            PhotosDlnaRenderersDialogPrivate);
  priv = self->priv;
  priv->item_mngr = photos_item_manager_dup_singleton ();
  priv->renderers_mngr = photos_dlna_renderers_manager_dup_singleton ();
  priv->remote_mngr = photos_remote_display_manager_dup_singleton ();
  priv->mode_cntrlr = photos_mode_controller_dup_singleton ();

  gtk_widget_init_template (GTK_WIDGET (self));

  gtk_list_box_set_header_func (priv->listbox, photos_dlna_renderers_separator_cb, NULL, NULL);

  renderers = photos_dlna_renderers_manager_dup_renderers (priv->renderers_mngr);

  while (renderers != NULL)
    {
      PhotosDlnaRenderer *renderer = PHOTOS_DLNA_RENDERER (renderers->data);

      photos_dlna_renderers_dialog_add_renderer (self, renderer);
      renderers = g_list_delete_link (renderers, renderers);
    }

  g_signal_connect (self, "response", G_CALLBACK (photos_dlna_renderers_dialog_response_cb), NULL);
}

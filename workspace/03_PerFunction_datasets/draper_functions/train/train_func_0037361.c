avatar_chooser_set_image (TpawAvatarChooser *self,
    GArray *avatar,
    gchar *mime_type,
    GdkPixbuf *pixbuf,
    gboolean maybe_convert)
{
  GdkPixbuf *pixbuf_view;
  GtkWidget *image;

  g_assert (avatar != NULL);
  g_assert (pixbuf != NULL);

  if (maybe_convert)
    {
      GArray *conv_avatar = NULL;
      gchar *conv_mime_type = NULL;

      if (!avatar_chooser_maybe_convert_and_scale (self,
              pixbuf, avatar, mime_type, &conv_avatar, &conv_mime_type))
        return;


      tp_clear_pointer (&self->priv->avatar, g_array_unref);
      self->priv->avatar = conv_avatar;

      g_free (self->priv->mime_type);
      self->priv->mime_type = conv_mime_type;
    }
  else
    {
      tp_clear_pointer (&self->priv->avatar, g_array_unref);
      self->priv->avatar = g_array_ref (avatar);

      g_free (self->priv->mime_type);
      self->priv->mime_type = g_strdup (mime_type);
    }

  self->priv->changed = TRUE;

  pixbuf_view = tpaw_pixbuf_scale_down_if_necessary (pixbuf,
      AVATAR_SIZE_VIEW);
  image = gtk_image_new_from_pixbuf (pixbuf_view);

  gtk_button_set_image (GTK_BUTTON (self), image);

  g_object_unref (pixbuf_view);
  g_object_unref (pixbuf);
}

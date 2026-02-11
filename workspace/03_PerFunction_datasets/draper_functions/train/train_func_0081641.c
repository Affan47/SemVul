get_avatar_cb (GObject *source,
    GAsyncResult *result,
    gpointer user_data)
{
  TpWeakRef *wr = user_data;
  TpawAvatarChooser *self = tp_weak_ref_dup_object (wr);
  const GArray *avatar;
  GdkPixbuf *pixbuf;
  gchar *mime_type;
  GError *error = NULL;

  if (self == NULL)
    {
      tp_weak_ref_destroy (wr);
      return;
    }

  avatar = tp_account_get_avatar_finish (self->priv->account, result, &error);
  if (avatar == NULL)
    {
      DEBUG ("Error getting account's avatar: %s", error->message);
      g_clear_error (&error);
      goto out;
    }

  if (avatar->len == 0)
    {
      avatar_chooser_clear_image (self);
      goto out;
    }

  pixbuf = tpaw_pixbuf_from_data_and_mime ((gchar *) avatar->data,
      avatar->len, &mime_type);
  if (pixbuf == NULL)
    {
      DEBUG ("couldn't make a pixbuf from avatar; giving up");
      goto out;
    }

  avatar_chooser_set_image (self, (GArray *) avatar, mime_type, pixbuf, FALSE);
  g_free (mime_type);

  self->priv->changed = FALSE;

out:
  tp_weak_ref_destroy (wr);
  g_object_unref (self);
}

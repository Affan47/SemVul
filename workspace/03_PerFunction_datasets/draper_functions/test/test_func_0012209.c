photos_remote_display_manager_share_cb (GObject      *source_object,
                                        GAsyncResult *res,
                                        gpointer      user_data)
{
  Share *share = user_data;
  PhotosDlnaRenderer *renderer = PHOTOS_DLNA_RENDERER (source_object);
  PhotosBaseItem *item;
  GError *error = NULL;

  item = photos_dlna_renderer_share_finish (renderer, res, &error);

  if (error != NULL)
    {
      g_warning ("Unable to remotely display item '%s': %s",
                 share->item != NULL ? photos_base_item_get_id (share->item) : "(none)",
                 error->message);
      g_signal_emit (share->manager, signals[SHARE_ERROR], 0, share->renderer, share->item, error);
      g_error_free (error);
      goto out;
    }

  g_object_unref (item);
  g_signal_emit (share->manager, signals[SHARE_BEGAN], 0, share->renderer, share->item);

out:
  photos_remote_display_manager_share_destroy (share);
}

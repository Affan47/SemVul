clutter_image_set_data (ClutterImage     *image,
                        const guint8     *data,
                        CoglPixelFormat   pixel_format,
                        guint             width,
                        guint             height,
                        guint             row_stride,
                        GError          **error)
{
  ClutterImagePrivate *priv;

  g_return_val_if_fail (CLUTTER_IS_IMAGE (image), FALSE);
  g_return_val_if_fail (data != NULL, FALSE);

  priv = image->priv;

  if (priv->texture != NULL)
    cogl_object_unref (priv->texture);

  priv->texture = cogl_texture_new_from_data (width, height,
                                              COGL_TEXTURE_NONE,
                                              pixel_format,
                                              COGL_PIXEL_FORMAT_ANY,
                                              row_stride,
                                              data);
  if (priv->texture == NULL)
    {
      g_set_error_literal (error, CLUTTER_IMAGE_ERROR,
                           CLUTTER_IMAGE_ERROR_INVALID_DATA,
                           _("Unable to load image data"));
      return FALSE;
    }

  clutter_content_invalidate (CLUTTER_CONTENT (image));

  return TRUE;
}

clutter_image_set_area (ClutterImage                 *image,
                        const guint8                 *data,
                        CoglPixelFormat               pixel_format,
                        const cairo_rectangle_int_t  *area,
                        guint                         row_stride,
                        GError                      **error)
{
  ClutterImagePrivate *priv;

  g_return_val_if_fail (CLUTTER_IS_IMAGE (image), FALSE);
  g_return_val_if_fail (data != NULL, FALSE);
  g_return_val_if_fail (area != NULL, FALSE);

  priv = image->priv;

  if (priv->texture == NULL)
    {
      priv->texture = cogl_texture_new_from_data (area->width,
                                                  area->height,
                                                  COGL_TEXTURE_NONE,
                                                  pixel_format,
                                                  COGL_PIXEL_FORMAT_ANY,
                                                  row_stride,
                                                  data);
    }
  else
    {
      gboolean res;

      res = cogl_texture_set_region (priv->texture,
                                     0, 0,
                                     area->x, area->y,
                                     area->width, area->height,
                                     area->width, area->height,
                                     pixel_format,
                                     row_stride,
                                     data);

      if (!res)
        {
          cogl_object_unref (priv->texture);
          priv->texture = NULL;
        }
    }

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

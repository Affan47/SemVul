load_sliced_image (GSimpleAsyncResult *result,
                   GObject *object,
                   GCancellable *cancellable)
{
  AsyncImageData *data;
  GList *res = NULL;
  GdkPixbuf *pix;
  gint width, height, y, x;

  g_assert (!cancellable);

  data = g_object_get_data (G_OBJECT (result), "load_sliced_image");
  g_assert (data);

  if (!(pix = gdk_pixbuf_new_from_file (data->path, NULL)))
    return;

  width = gdk_pixbuf_get_width (pix);
  height = gdk_pixbuf_get_height (pix);
  for (y = 0; y < height; y += data->grid_height)
    {
      for (x = 0; x < width; x += data->grid_width)
        {
          GdkPixbuf *pixbuf = gdk_pixbuf_new_subpixbuf (pix, x, y, data->grid_width, data->grid_height);
          g_assert (pixbuf != NULL);
          res = g_list_append (res, pixbuf);
        }
    }


  g_object_unref (pix);
  g_simple_async_result_set_op_res_gpointer (result, res, free_glist_unref_gobjects);
}

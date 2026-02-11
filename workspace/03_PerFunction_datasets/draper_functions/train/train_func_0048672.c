goo_canvas_image_new (GooCanvasItem *parent,
		      GdkPixbuf     *pixbuf,
		      gdouble        x,
		      gdouble        y,
		      ...)
{
  GooCanvasItem *item;
  GooCanvasImage *image;
  GooCanvasImageData *image_data;
  const char *first_property;
  va_list var_args;

  item = g_object_new (GOO_TYPE_CANVAS_IMAGE, NULL);
  image = (GooCanvasImage*) item;

  image_data = image->image_data;
  image_data->x = x;
  image_data->y = y;

  if (pixbuf)
    {
      image_data->pattern = goo_canvas_cairo_pattern_from_pixbuf (pixbuf);
      image_data->width = gdk_pixbuf_get_width (pixbuf);
      image_data->height = gdk_pixbuf_get_height (pixbuf);
      image_data->width_ref = image_data->width;
      image_data->height_ref = image_data->height;
    }

  va_start (var_args, y);
  first_property = va_arg (var_args, char*);
  if (first_property)
    g_object_set_valist ((GObject*) item, first_property, var_args);
  va_end (var_args);

  if (parent)
    {
      goo_canvas_item_add_child (parent, item, -1);
      g_object_unref (item);
    }

  return item;
}

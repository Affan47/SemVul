clutter_color_init (ClutterColor *color,
                    guint8        red,
                    guint8        green,
                    guint8        blue,
                    guint8        alpha)
{
  g_return_val_if_fail (color != NULL, NULL);

  color->red = red;
  color->green = green;
  color->blue = blue;
  color->alpha = alpha;

  return color;
}

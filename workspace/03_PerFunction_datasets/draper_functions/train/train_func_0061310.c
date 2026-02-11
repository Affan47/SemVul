get_flag(const struct nation_type *nation)
{
  int x0, y0, x1, y1, w, h;
  GdkPixbuf *im;
  struct sprite *flag;

  flag = get_nation_flag_sprite(tileset, nation);


  sprite_get_bounding_box(flag, &x0, &y0, &x1, &y1);

  fc_assert_ret_val(x0 != -1, NULL);
  fc_assert_ret_val(y0 != -1, NULL);
  fc_assert_ret_val(x1 != -1, NULL);
  fc_assert_ret_val(y1 != -1, NULL);

  w = (x1 - x0) + 1;
  h = (y1 - y0) + 1;


  fc_assert_ret_val(w >= MIN_DIMENSION && h >= MIN_DIMENSION, NULL);


  im = gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE, 8, w, h);
  if (im != NULL) {
    GdkPixbuf *pixbuf = sprite_get_pixbuf(flag);

    gdk_pixbuf_copy_area(pixbuf, x0, y0, w, h,
                         im, 0, 0);
    g_object_unref(G_OBJECT(pixbuf));
  }


  return im;
}

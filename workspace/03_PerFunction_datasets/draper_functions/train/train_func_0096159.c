crop_sprite(struct sprite *source,
			   int x, int y,
			   int width, int height,
			   struct sprite *mask,
			   int mask_offset_x, int mask_offset_y)
{
  GdkPixbuf *mypixbuf, *sub, *mask_pixbuf;


  if (x < 0) {
    width += x;
    x = 0;
  }
  if (y < 0) {
    height += y;
    y = 0;
  }
  width = CLIP(0, width, source->width - x);
  height = CLIP(0, height, source->height - y);
  sub = gdk_pixbuf_new_subpixbuf(sprite_get_pixbuf(source), x, y,
				 width, height);
  mypixbuf = gdk_pixbuf_copy(sub);
  g_object_unref(sub);


  if (mask
      && (mask_pixbuf = sprite_get_pixbuf(mask))
      && gdk_pixbuf_get_has_alpha(mask_pixbuf)) {
    int x1, y1;


    mask_offset_x -= x;
    mask_offset_y -= y;

    width = CLIP(0, width, mask->width + mask_offset_x);
    height = CLIP(0, height, mask->height + mask_offset_y);

    if (!gdk_pixbuf_get_has_alpha(mypixbuf)) {
      GdkPixbuf *p2 = mypixbuf;

      mypixbuf = gdk_pixbuf_add_alpha(mypixbuf, FALSE, 0, 0, 0);
      g_object_unref(p2);
    }

    for (x1 = 0; x1 < width; x1++) {
      for (y1 = 0; y1 < height; y1++) {
	int mask_x = x1 - mask_offset_x, mask_y = y1 - mask_offset_y;
	guchar *alpha = gdk_pixbuf_get_pixels(mypixbuf)
	  + y1 * gdk_pixbuf_get_rowstride(mypixbuf)
	  + x1 * gdk_pixbuf_get_n_channels(mypixbuf)
	  + 3;
	guchar *mask_alpha = gdk_pixbuf_get_pixels(mask_pixbuf)
	  + mask_y * gdk_pixbuf_get_rowstride(mask_pixbuf)
	  + mask_x * gdk_pixbuf_get_n_channels(mask_pixbuf)
	  + 3;

	*alpha = (*alpha) * (*mask_alpha) / 255;
      }
    }
  }

  return ctor_sprite(mypixbuf);
}

pixmap_put_overlay_tile(Pixmap pixmap, int canvas_x, int canvas_y,
 				    struct sprite *ssprite)
{
  if (!ssprite) return;

  pixmap_put_sprite(pixmap, canvas_x, canvas_y,
		    ssprite, 0, 0, ssprite->width, ssprite->height);
}

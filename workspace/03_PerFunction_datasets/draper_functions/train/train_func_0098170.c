start_frigate_anim()
{
  GdkPixbuf *pixmap;
  int w;

  if(!with_frigate)
    return;

  if (frigate_item)
    stop_frigate_anim();


  pixmap = gc_pixmap_load("submarine/asw_frigate.png");
  w = gdk_pixbuf_get_width(pixmap);

  frigate_item = goo_canvas_image_new (goo_canvas_get_root_item(gcomprisBoard->canvas),
				       pixmap,
				       0,
				       0,
				       NULL);
  goo_canvas_item_translate(frigate_item, BOARDWIDTH, 6);
  goo_canvas_item_animate(frigate_item,
			  -w,
			  2.0,
			  1,
			  0,
			  TRUE,
			  100*1000,
			  100,
			  GOO_CANVAS_ANIMATE_RESTART);
#if GDK_PIXBUF_MAJOR <= 2 && GDK_PIXBUF_MINOR <= 24
  gdk_pixbuf_unref(pixmap);
#else
  g_object_unref(pixmap);
#endif
}

make_picker_cursor (GdkScreen *screen)
{
  GdkCursor *cursor;

  cursor = gdk_cursor_new_from_name (gdk_screen_get_display (screen),
				     "color-picker");

  if (!cursor)
    {
      GdkColor bg = { 0, 0xffff, 0xffff, 0xffff };
      GdkColor fg = { 0, 0x0000, 0x0000, 0x0000 };
      GdkWindow *window;
      GdkPixmap *pixmap, *mask;

      window = gdk_screen_get_root_window (screen);

      pixmap =
	gdk_bitmap_create_from_data (window, (gchar *) dropper_bits,
				     DROPPER_WIDTH, DROPPER_HEIGHT);

      mask =
	gdk_bitmap_create_from_data (window, (gchar *) dropper_mask,
				     DROPPER_WIDTH, DROPPER_HEIGHT);

      cursor = gdk_cursor_new_from_pixmap (pixmap, mask, &fg, &bg,
					   DROPPER_X_HOT, DROPPER_Y_HOT);

      g_object_unref (pixmap);
      g_object_unref (mask);
    }

  return cursor;
}

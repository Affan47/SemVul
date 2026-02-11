gfx_load_pixmaps (void)
{
  gchar *fname;
  GdkPixbuf *pb_tileset_tmp;
  GdkPixbuf *pb_bground_tmp = NULL;


  while (TRUE) {
    fname = g_build_filename (DATA_DIRECTORY, theme[p.theme_id].fname_tileset, NULL);
    pb_tileset_tmp = gdk_pixbuf_new_from_file (fname, NULL);
    if (pb_tileset_tmp == NULL) {
      if (p.theme_id != 0) {
	p.theme_id = 0;
	g_free (fname);
	continue;
      } else {
	gfx_load_error (fname);
	g_free (fname);
	return FALSE;
      }
    }

    g_free (fname);
    break;
  }

  if (pb_tileset_raw)
    g_object_unref (pb_tileset_raw);

  pb_tileset_raw = pb_tileset_tmp;

  if (theme[p.theme_id].fname_bground != NULL) {
    fname = g_build_filename (DATA_DIRECTORY, theme[p.theme_id].fname_bground, NULL);
    pb_bground_tmp = gdk_pixbuf_new_from_file (fname, NULL);
    if (pb_bground_tmp == NULL) {
      gfx_load_error (fname);
      g_object_unref (pb_tileset_tmp);
      g_free (fname);
      return FALSE;
    }
    g_free (fname);
  }

  if (pb_bground_raw)
    g_object_unref (pb_bground_raw);


  if (pb_bground_tmp != NULL) {
    pb_bground_raw = pb_bground_tmp;
  } else {
    gint tilesize_raw;
    gint i, j;

    tilesize_raw = gdk_pixbuf_get_height (pb_tileset_raw);

    pb_bground_raw = gdk_pixbuf_new (GDK_COLORSPACE_RGB, TRUE, 8,
				     tilesize_raw * 7, tilesize_raw * 7);
    for (i = 0; i < 7; i++) {
      gdk_pixbuf_copy_area (pb_tileset_raw,
			    tilesize_raw * 3, 0,
			    tilesize_raw, tilesize_raw,
			    pb_bground_raw, i * tilesize_raw, 0);
      for (j = 1; j < 7; j++) {
	gdk_pixbuf_copy_area (pb_tileset_raw,
			      tilesize_raw * 2, 0,
			      tilesize_raw, tilesize_raw,
			      pb_bground_raw,
			      i * tilesize_raw, j * tilesize_raw);
      }
    }
  }

  return TRUE;
}

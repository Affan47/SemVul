gst_pngdec_libpng_init (GstPngDec * pngdec)
{
  g_return_val_if_fail (GST_IS_PNGDEC (pngdec), FALSE);

  GST_LOG ("init libpng structures");


  pngdec->png = png_create_read_struct (PNG_LIBPNG_VER_STRING,
      (png_voidp) NULL, user_error_fn, user_warning_fn);

  if (pngdec->png == NULL)
    goto init_failed;

  pngdec->info = png_create_info_struct (pngdec->png);
  if (pngdec->info == NULL)
    goto info_failed;

  pngdec->endinfo = png_create_info_struct (pngdec->png);
  if (pngdec->endinfo == NULL)
    goto endinfo_failed;

  png_set_progressive_read_fn (pngdec->png, pngdec,
      user_info_callback, user_endrow_callback, user_end_callback);

  return TRUE;


init_failed:
  {
    GST_ELEMENT_ERROR (pngdec, LIBRARY, INIT, (NULL),
        ("Failed to initialize png structure"));
    return FALSE;
  }
info_failed:
  {
    GST_ELEMENT_ERROR (pngdec, LIBRARY, INIT, (NULL),
        ("Failed to initialize info structure"));
    return FALSE;
  }
endinfo_failed:
  {
    GST_ELEMENT_ERROR (pngdec, LIBRARY, INIT, (NULL),
        ("Failed to initialize endinfo structure"));
    return FALSE;
  }
}

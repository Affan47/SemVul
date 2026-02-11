p_lib_save_named_image_1(gint32 image_id, const char *sav_name, GimpRunMode run_mode, gboolean enable_thumbnailsave
  , const char *l_basename
  , const char *l_extension
  )
{
  GAPJpegSaveVals   *jpg_save_vals;
  gint32 l_sav_rc;
  char *l_key_save_vals_jpg;


  l_sav_rc = -1;
  jpg_save_vals = NULL;

  l_key_save_vals_jpg = g_strdup_printf("GIMP_GAP_SAVE_VALS_JPG_%s%s"
                       ,l_basename
                       ,l_extension
                       );

  if(gap_debug)
  {
    printf("p_lib_save_named_image_1: runmode:%d  sav_name:%s\n .. l_key_save_vals_jpg:%s\n  .. base:%s\n  .. ext:%s\n"
      ,run_mode
      ,sav_name
      ,l_key_save_vals_jpg
      ,l_basename
      ,l_extension
      );
  }


  if (run_mode != GIMP_RUN_INTERACTIVE)
  {
    int jpg_parsize;

    jpg_parsize = gimp_get_data_size(l_key_save_vals_jpg);
    if(gap_debug)
    {
      printf("p_lib_save_named_image_1: jpg_parsize=%d\n"
        ,jpg_parsize
        );
    }

    if (jpg_parsize > 0)
    {
      jpg_save_vals = g_malloc(jpg_parsize);
      gimp_get_data (l_key_save_vals_jpg, jpg_save_vals);
      run_mode = GIMP_RUN_NONINTERACTIVE;
    }
  }

  l_sav_rc = p_lib_save_named_image2(image_id
                           , sav_name
                           , run_mode
                           , FALSE
                           , jpg_save_vals
                           );
  if (jpg_save_vals != NULL)
  {
    g_free(jpg_save_vals);
  }


  if ((run_mode == GIMP_RUN_INTERACTIVE) && (p_extension_is_jpeg(l_extension)))
  {
    GimpParasite      *jpg_save_parasite;

    jpg_save_parasite = gimp_image_parasite_find (image_id,
                                      "jpeg-save-options");
    if(gap_debug)
    {
      printf("DEBUG: jpg_save_parasite %d\n", (int)jpg_save_parasite);
    }
    if (jpg_save_parasite)
    {
      const GAPJpegSaveVals   *const_jpg_save_vals;
      const_jpg_save_vals = gimp_parasite_data (jpg_save_parasite);


      gimp_set_data (l_key_save_vals_jpg, const_jpg_save_vals, sizeof(GAPJpegSaveVals));
      gimp_parasite_free (jpg_save_parasite);
    }
  }

  g_free(l_key_save_vals_jpg);

  return (l_sav_rc);
}

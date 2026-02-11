p_build_wp_set_table(GapMorphGlobalParams  *mgpp
                    ,GapMorphExeLayerstack *mlayers
                    )
{
  long lower_num;
  long upper_num;
  gchar *lower_basename;
  gchar *upper_basename;
  gchar *lower_ext;
  gchar *upper_ext;

  lower_basename = gap_lib_alloc_basename(mgpp->workpoint_file_lower
                                         ,&lower_num);
  upper_basename = gap_lib_alloc_basename(mgpp->workpoint_file_upper
                                         ,&upper_num);
  lower_ext = gap_lib_alloc_extension(mgpp->workpoint_file_lower);
  upper_ext = gap_lib_alloc_extension(mgpp->workpoint_file_upper);

  if((lower_num != upper_num)
  && (strcmp(lower_basename, upper_basename) == 0)
  && (strcmp(lower_ext, upper_ext) == 0))
  {
    gchar *wp_filename;
    gint   ii;
    gint   wp_idx;

    if(gap_debug)
    {
      printf("p_build_wp_set_table: using multiple workpoint sets\n"
        " lower_basename:%s\n"
        " upper_basename:%s\n lower_num:%d upper_num:%d\n"
        ,lower_basename
        ,upper_basename
        ,(int)lower_num
        ,(int)upper_num
        );
    }


    mlayers->available_wp_sets = 0;
    for(ii=MIN(lower_num, upper_num); ii <= MAX(upper_num, lower_num); ii++)
    {
      wp_filename = g_strdup_printf("%s%02d%s"
                                   ,lower_basename
                                   ,(int)ii
                                   ,lower_ext
                                   );
      if(g_file_test(wp_filename, G_FILE_TEST_EXISTS))
      {
        mlayers->available_wp_sets++;
      }
      g_free(wp_filename);
    }

    mlayers->tab_wp_sets = g_new(GapMorphWarpCoreAPI*, mlayers->available_wp_sets);
    wp_idx = 0;
    for(ii=MIN(lower_num, upper_num); ii <= MAX(upper_num, lower_num); ii++)
    {
      wp_filename = g_strdup_printf("%s%02d%s"
                                   ,lower_basename
                                   ,(int)ii
                                   ,lower_ext
                                   );
      if(g_file_test(wp_filename, G_FILE_TEST_EXISTS))
      {
        if(wp_idx < mlayers->available_wp_sets)
        {
          if(gap_debug)
          {
            printf("p_build_wp_set_table: LOADING workpoint file: %s\n", wp_filename);
          }
          mlayers->tab_wp_sets[wp_idx] = p_load_workpoint_set(wp_filename, mgpp, mlayers);
        }
        wp_idx++;
      }
      g_free(wp_filename);
    }

  }
  else
  {

    if(gap_debug)
    {
      printf("p_build_wp_set_table: create 2 workpoint sets from upper and lower file\n lower:%s\n upper:%s\n"
        ,mgpp->workpoint_file_lower
        ,mgpp->workpoint_file_upper
        );
    }
    mlayers->available_wp_sets = 2;
    mlayers->tab_wp_sets = g_new(GapMorphWarpCoreAPI*, mlayers->available_wp_sets);
    mlayers->tab_wp_sets[0] = p_load_workpoint_set(mgpp->workpoint_file_lower, mgpp, mlayers);
    mlayers->tab_wp_sets[1] = p_load_workpoint_set(mgpp->workpoint_file_upper, mgpp, mlayers);
  }

  g_free(lower_basename);
  g_free(upper_basename);
  g_free(lower_ext);
  g_free(upper_ext);

}

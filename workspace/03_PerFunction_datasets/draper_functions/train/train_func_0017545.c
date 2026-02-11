p_alloc_ainfo_for_videofile(GapPlayerMainGlobalParams *gpp
                                , char *filename
                                , gint32 seltrack
                                , gdouble delace
                                , const char *preferred_decoder
                                )
{
  GapAnimInfo   *l_ainfo_ptr;

  l_ainfo_ptr = NULL;

#ifdef GAP_ENABLE_VIDEOAPI_SUPPORT
  if(filename == NULL)
  {
    return (NULL);
  }

  if(!g_file_test(filename, G_FILE_TEST_EXISTS))
  {
    if(gap_debug)
    {
      printf ("p_alloc_ainfo_for_videofile: file %s does not exist\n"
             , filename
              );
    }
    return (NULL);
  }

  if(!gap_story_filename_is_videofile_by_ext(filename))
  {
    if(gap_debug)
    {
      printf ("p_alloc_ainfo_for_videofile: file %s has no typical video extension\n"
             , filename
              );
    }
    if(!gpp->force_open_as_video)
    {
      return (NULL);
    }
  }

  gpp->gva_lock = TRUE;
  p_close_videofile(gpp);
  p_open_videofile(gpp, filename, seltrack, delace, preferred_decoder);
  gpp->gva_lock = FALSE;
  if(gpp->gvahand == NULL)
  {
    if(gap_debug)
    {
      printf ("p_alloc_ainfo_for_videofile: file %s NO compatible Decoder available\n"
             , filename
              );
    }
    return (NULL);
  }


  l_ainfo_ptr = (GapAnimInfo*)g_malloc(sizeof(GapAnimInfo));
  if(l_ainfo_ptr == NULL) return(NULL);

  l_ainfo_ptr->basename = g_strdup(filename);
  l_ainfo_ptr->extension = gap_lib_alloc_extension(filename);

  l_ainfo_ptr->new_filename = NULL;
  l_ainfo_ptr->image_id = -1;
  l_ainfo_ptr->old_filename = g_strdup(filename);
  l_ainfo_ptr->ainfo_type = GAP_AINFO_MOVIE;
  l_ainfo_ptr->seltrack = seltrack;
  l_ainfo_ptr->delace = delace;

  l_ainfo_ptr->curr_frame_nr = 1;
  l_ainfo_ptr->first_frame_nr = 1;
  l_ainfo_ptr->frame_cnt = gpp->gvahand->total_frames;
  if(!gpp->gvahand->all_frames_counted)
  {


    l_ainfo_ptr->frame_cnt *= 2;
  }
  l_ainfo_ptr->last_frame_nr = l_ainfo_ptr->frame_cnt;
  l_ainfo_ptr->width  = gpp->gvahand->width;
  l_ainfo_ptr->height = gpp->gvahand->height;
  gpp->original_speed = gpp->gvahand->framerate;

#endif
  return(l_ainfo_ptr);

}

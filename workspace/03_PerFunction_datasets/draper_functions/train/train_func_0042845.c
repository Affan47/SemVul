p_fetch_display_th_data_from_storyboard(GapPlayerMainGlobalParams *gpp
  , gint32   framenr
  , gchar  **ckey_pptr
  , gchar  **filename_pptr
  , gint32  *th_width_ptr
  , gint32  *th_height_ptr
  , gint32  *th_bpp_ptr
  , gint32  *flip_request_ptr
  , gint32  *flip_status_ptr
  )
{
  GapStoryLocateRet *stb_ret;
  guchar *l_th_data;

  l_th_data = NULL;
  stb_ret = gap_story_locate_framenr(gpp->stb_ptr
                                  , framenr
                                  , gpp->stb_in_track
                                  );
  if(stb_ret)
  {
    if((stb_ret->locate_ok)
    && (stb_ret->stb_elem))
    {
      *filename_pptr = gap_story_get_filename_from_elem_nr(stb_ret->stb_elem
                                              , stb_ret->ret_framenr
                                             );
      *flip_request_ptr = stb_ret->stb_elem->flip_request;
      if(stb_ret->stb_elem->record_type == GAP_STBREC_VID_MOVIE)
      {
         if(*filename_pptr)
         {
           if(gpp->use_thumbnails)
           {

             *th_width_ptr = gpp->pv_ptr->pv_width;
             *th_height_ptr = gpp->pv_ptr->pv_height;
           }
           else
           {

             *th_width_ptr = -1;
             *th_height_ptr = -1;
           }

           if (gpp->max_player_cache > 0)
           {
             *ckey_pptr = gap_player_cache_new_movie_key(*filename_pptr
                         , stb_ret->ret_framenr
                         , stb_ret->stb_elem->seltrack
                         , stb_ret->stb_elem->delace
                         );
           }
           l_th_data  = p_fetch_videoframe_via_cache(gpp
                         , *filename_pptr
                         , stb_ret->ret_framenr
                         , 1 + (abs(stb_ret->stb_elem->to_frame) - abs(stb_ret->stb_elem->from_frame))
                         , stb_ret->stb_elem->seltrack
                         , stb_ret->stb_elem->delace
                         , stb_ret->stb_elem->preferred_decoder
                         , th_bpp_ptr
                         , th_width_ptr
                         , th_height_ptr
                         , flip_status_ptr
                         , *ckey_pptr
                         );
           if(gpp->cancel_video_api)
           {
             if(l_th_data)
             {
               g_free(l_th_data);
               l_th_data = NULL;
             }
             if(gpp->progress_bar)
             {
                gtk_progress_bar_set_text(GTK_PROGRESS_BAR(gpp->progress_bar)
                             , _("Canceled"));
             }
           }
           g_free(*filename_pptr);
           *filename_pptr = NULL;
         }
      }
    }
    g_free(stb_ret);
  }

  return (l_th_data);
}

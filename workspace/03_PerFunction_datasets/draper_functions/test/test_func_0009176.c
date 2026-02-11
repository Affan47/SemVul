p_open_videofile(GapPlayerMainGlobalParams *gpp
                , char *filename
                , gint32 seltrack
                , gdouble delace
                , const char *preferred_decoder
                )
{
  char *vindex_file;
  gboolean    l_have_valid_vindex;
  l_have_valid_vindex = FALSE;

#ifdef GAP_ENABLE_VIDEOAPI_SUPPORT

  p_reopen_videofile(gpp, filename, seltrack, delace, preferred_decoder);

  vindex_file = NULL;

  if(gpp->gvahand)
  {

    {
      t_GVA_DecoderElem *dec_elem;

      dec_elem = (t_GVA_DecoderElem *)gpp->gvahand->dec_elem;
      if(dec_elem->decoder_name)
      {
        vindex_file = GVA_build_videoindex_filename(gpp->gva_videofile
                                             ,1
                                             ,dec_elem->decoder_name
                                             );
      }
    }

    if(gpp->gvahand->vindex)
    {
      if(gpp->gvahand->vindex->total_frames > 0)
      {
        l_have_valid_vindex = TRUE;
      }
    }

    if((l_have_valid_vindex == FALSE)
    &&(gpp->startup == FALSE))
    {
      gboolean vindex_permission;
      t_GVA_SeekSupport seekSupp;

      gpp->cancel_video_api = FALSE;
      gpp->request_cancel_video_api = FALSE;
      if(gpp->progress_bar)
      {
        gtk_progress_bar_set_text(GTK_PROGRESS_BAR(gpp->progress_bar), _("seek-selftest"));
      }
      seekSupp = GVA_check_seek_support(gpp->gvahand);


      vindex_permission = gap_arr_create_vindex_permission(gpp->gva_videofile
                            , vindex_file
                            , (gint32)seekSupp
                            );

      if(vindex_permission)
      {


        gpp->cancel_video_api = FALSE;
        gpp->request_cancel_video_api = FALSE;
        if(gpp->progress_bar)
        {
           gtk_progress_bar_set_text(GTK_PROGRESS_BAR(gpp->progress_bar), _("Creating Index"));
        }
        gpp->gvahand->create_vindex = TRUE;


        gtk_widget_hide (gpp->play_n_stop_hbox);
        gtk_widget_show (gpp->cancel_vindex_button);


        gpp->vindex_creation_is_running = TRUE;
        GVA_count_frames(gpp->gvahand);
        gpp->vindex_creation_is_running = FALSE;


        gtk_widget_hide (gpp->cancel_vindex_button);
        gtk_widget_show (gpp->play_n_stop_hbox);

        if(!gpp->cancel_video_api)
        {
          if(gpp->gvahand->vindex != NULL)
          {
            p_update_ainfo_for_videofile(gpp);
            p_update_ainfo_dependent_widgets(gpp);

            p_reopen_videofile(gpp, filename, seltrack, delace, preferred_decoder);
          }
          else
          {
            g_message(_("No videoindex available. "
                        "Access is limited to (slow) sequential read "
                        "on file: %s")
                     , gpp->gvahand->filename
                     );
          }
        }
      }
    }


    if(vindex_file)
    {
      g_free(vindex_file);
    }

  }

#endif

}

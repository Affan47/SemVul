p_prefetch_vthumbs (GapStbMainGlobalParams *sgpp, GapStoryBoard *stb)
{
  GapStorySection  *section;
  GapStoryElem     *stb_elem;
  GapVThumbElem    *vthumb;
  gint32         l_total;
  gint32         l_count;


  if(stb == NULL)
  {
    return;
  }

  if(gap_debug)
  {
    printf("p_prefetch_vthumbs : stb: %d\n"
       ,(int)stb
       );
  }

  l_total = 0;
  for(section = stb->stb_section; section != NULL; section = section->next)
  {
    for(stb_elem = section->stb_elem; stb_elem != NULL;  stb_elem = stb_elem->next)
    {
      if(stb_elem->record_type == GAP_STBREC_VID_MOVIE)
      {
        l_total++;
      }
    }
  }

  l_count = 0;
  for(section = stb->stb_section; section != NULL; section = section->next)
  {
    for(stb_elem = section->stb_elem; stb_elem != NULL;  stb_elem = stb_elem->next)
    {
      if(stb_elem->record_type == GAP_STBREC_VID_MOVIE)
      {
        gchar  *msg;

        if((sgpp->cancel_video_api) || (sgpp->auto_vthumb_refresh_canceled == TRUE) || (sgpp->auto_vthumb != TRUE))
        {
          if(sgpp->progress_bar_master)
          {
            gtk_progress_bar_set_text(GTK_PROGRESS_BAR(sgpp->progress_bar_master),
                                     _("videothumbnail cancelled"));
            gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(sgpp->progress_bar_master), 0);
          }
          if(gap_debug)
          {
            printf("p_prefetch_vthumbs : (1) videothumbnail cancelled: cancel_video_api: %d auto_vthumb_refresh_canceled:%d auto_vthumb:%d\n"
               ,(int)sgpp->cancel_video_api
               ,(int)sgpp->auto_vthumb_refresh_canceled
               ,(int)sgpp->auto_vthumb
               );
          }
          return;
        }

        l_count++;

        vthumb = gap_story_vthumb_elem_fetch(sgpp
                    ,stb
                    ,stb_elem
                    ,stb_elem->from_frame
                    ,stb_elem->seltrack
                    ,gap_story_get_preferred_decoder(stb, stb_elem)
                    );
        if(sgpp->progress_bar_master)
        {

           msg = g_strdup_printf(_("Fetching videothumbnail for clip: %d (out of %d)")
                                ,(int)l_count
                                ,(int)l_total
                                );
           gtk_progress_bar_set_text(GTK_PROGRESS_BAR(sgpp->progress_bar_master), msg);
           gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(sgpp->progress_bar_master)
                                        ,(gdouble)l_count / (gdouble)l_total
                                        );

           gap_story_vthumb_g_main_context_iteration(sgpp);


           if (sgpp->vthumb_prefetch_in_progress != GAP_VTHUMB_PREFETCH_IN_PROGRESS)
           {
             if(gap_debug)
             {
               printf("p_prefetch_vthumbs: prefetch PROGRESS interrupt occured\n");
             }


             p_reset_progress_bars(sgpp);
             return;
           }


        }
      }
    }
  }

  if(gap_debug)
  {
    printf("p_prefetch_vthumbs : Loop done\n");
  }
  p_reset_progress_bars(sgpp);

}

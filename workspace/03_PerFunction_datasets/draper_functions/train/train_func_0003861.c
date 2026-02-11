gap_cme_gui_check_storyboard_file(GapCmeGlobalParams *gpp)
{
   gboolean joinable;
   t_global_stb    *gstb;
  gint32 l_first_frame_limit;
  gint32 l_last_frame_nr;
  GapLibTypeInputRange l_rangetype;

  gstb = &global_stb;
  p_get_range_and_type (gpp, &l_first_frame_limit, &l_last_frame_nr, &l_rangetype);

  gstb->total_stroyboard_frames = 0;
  gstb->first_frame_limit  = l_first_frame_limit;
  gstb->last_frame_nr      = l_last_frame_nr;
  gpp->val.input_mode      = l_rangetype;
  gstb->composite_audio[0] = '\0';
  gstb->aud_total_sec      = 0.0;

  p_range_widgets_set_limits(gpp
                             , l_first_frame_limit
                             , l_last_frame_nr
                             , l_rangetype
                             );

  if(gpp->ecp == NULL)
  {
    return;
  }


  if(gpp->val.storyboard_file[0] == '\0')
  {
    p_print_storyboard_text_label(gpp, NULL);
    return;
  }
  if(!g_file_test(gpp->val.storyboard_file, G_FILE_TEST_EXISTS))
  {
    p_print_storyboard_text_label(gpp, NULL);
     return;
  }


#ifdef GAP_USE_GTHREAD
  if(gap_cme_gui_check_gui_thread_is_active(gpp))  { return; }
  if(gstb->poll_timertag >= 0)           { return; }


  p_print_storyboard_text_label(gpp, _("Checking Storyboard File") );

  gstb->progress = 0.0;
  g_snprintf(gstb->status_msg, sizeof(gstb->status_msg), _("Parsing Storyboardfile"));

  gstb->stb_job_done  = FALSE;


  if(gap_debug) printf("MASTER: Before storyborad g_thread_create\n");

  joinable = TRUE;
  gpp->val.gui_proc_thread =
      g_thread_create((GThreadFunc)p_thread_storyboard_file
                     , NULL
                     , joinable
                     , NULL
                     );

  if(gap_debug) printf("MASTER: After storyborad g_thread_create\n");


  gstb->poll_timertag =
    (gint32) g_timeout_add(500, (GSourceFunc) on_timer_poll, gstb);


#else


  {
    gboolean do_processing;

    do_processing = TRUE;


    if (!gpp->storyboard_create_composite_audio)
    {
      static GapArrArg  argv[1];

      do_processing = FALSE;

      gap_arr_arg_init(&argv[0], GAP_ARR_WGT_LABEL);
      argv[0].label_txt = _("Go for checking storyboard file");

      if(gap_arr_ok_cancel_dialog(_("Storyboardfile Check")
                               ,_("Storyboardfile Check")
                               ,1
                               ,argv
                               ))
      {
        do_processing = TRUE;
      }
    }

    if(do_processing)
    {
      p_thread_storyboard_file(NULL);
      p_storybord_job_finished(gpp, gstb);
    }
  }
#endif


}

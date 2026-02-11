gap_arr_confirm_dialog(const char *msg_txt, const char *title_txt, const char *frame_txt)
{
  static GapArrButtonArg  l_but_argv[2];
  static GapArrArg  l_argv[1];
  gboolean          l_continue;
  gboolean          l_confirm;
  char *value_string;

  l_confirm = TRUE;
  value_string = gimp_gimprc_query("video-confirm-frame-delete");
  if(value_string)
  {

     if(gap_debug) printf("video-confirm-frame-delete: %s\n", value_string);


     if((*value_string == 'n') || (*value_string == 'N'))
     {
       l_confirm = FALSE;
     }
     g_free(value_string);
  }
  else
  {
     if(gap_debug) printf("NOT found in gimprc: video-confirm-frame-delete:\n (CONFIRM default yes is used)");
  }

  if(!l_confirm)
  {

    return TRUE;
  }


  l_but_argv[0].but_txt  = GTK_STOCK_CANCEL;
  l_but_argv[0].but_val  = -1;
  l_but_argv[1].but_txt  = GTK_STOCK_OK;
  l_but_argv[1].but_val  = 0;


  gap_arr_arg_init(&l_argv[0], GAP_ARR_WGT_LABEL);
  l_argv[0].label_txt = msg_txt;

  l_continue = gap_arr_std_dialog (title_txt
                                  ,frame_txt
                                  ,G_N_ELEMENTS(l_argv),     l_argv
                                  ,G_N_ELEMENTS(l_but_argv), l_but_argv
                                  ,-1
                                  );

  if(l_continue == 0)
  {
    return TRUE;
  }

  return FALSE;

}

p_update_framenr_labels(GapStbAttrWidget *attw, gint img_idx, gint32 framenr)
{
  char    txt_buf[100];
  gdouble l_speed_fps;

  if(attw == NULL) { return; }
  if(attw->stb_elem_refptr == NULL) { return; }


  g_snprintf(txt_buf, sizeof(txt_buf), "%d  "
            ,(int)framenr
            );
  gtk_label_set_text ( GTK_LABEL(attw->gfx_tab[img_idx].framenr_label), txt_buf);

  l_speed_fps = GAP_STORY_DEFAULT_FRAMERATE;
  if(attw->stb_refptr)
  {
    if(attw->stb_refptr->master_framerate > 0)
    {
      l_speed_fps = attw->stb_refptr->master_framerate;
    }
  }

  gap_timeconv_framenr_to_timestr(framenr -1
                         , l_speed_fps
                         , txt_buf
                         , sizeof(txt_buf)
                         );
  gtk_label_set_text ( GTK_LABEL(attw->gfx_tab[img_idx].frametime_label), txt_buf);

}

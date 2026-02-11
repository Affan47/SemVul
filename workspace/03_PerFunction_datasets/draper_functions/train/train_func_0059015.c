p_frames_layer_del(GapAnimInfo *ainfo_ptr,
                   long range_from, long range_to, long position)
{
  gint32  l_tmp_image_id;

  long    l_cur_frame_nr;
  long    l_step, l_begin, l_end;
  gint32  l_tmp_layer_id;
  gint       l_nlayers;
  gint32    *l_layers_list;
  gdouble    l_percentage, l_percentage_step;
  gchar     *l_buff;
  int        l_rc;


  l_rc = 0;
  l_percentage = 0.0;
  if(ainfo_ptr->run_mode == GIMP_RUN_INTERACTIVE)
  {
    l_buff = g_strdup_printf (_("Removing layer (pos:%ld) from frames..."), position);
    gimp_progress_init(l_buff);
    g_free (l_buff);
  }


  l_begin = range_from;
  l_end   = range_to;

  if(range_from > range_to)
  {
    l_step  = -1;
    l_percentage_step = 1.0 / ((1.0 + range_from) - range_to);

    if(range_to < ainfo_ptr->first_frame_nr)
    { l_begin = ainfo_ptr->first_frame_nr;
    }
    if(range_from > ainfo_ptr->last_frame_nr)
    { l_end = ainfo_ptr->last_frame_nr;
    }
  }
  else
  {
    l_step  = 1;
    l_percentage_step = 1.0 / ((1.0 + range_to) - range_from);

    if(range_from < ainfo_ptr->first_frame_nr)
    { l_begin = ainfo_ptr->first_frame_nr;
    }
    if(range_to > ainfo_ptr->last_frame_nr)
    { l_end = ainfo_ptr->last_frame_nr;
    }
  }


  l_cur_frame_nr = l_begin;
  while(1)
  {

    if(ainfo_ptr->new_filename != NULL) g_free(ainfo_ptr->new_filename);
    ainfo_ptr->new_filename = gap_lib_alloc_fname(ainfo_ptr->basename,
                                        l_cur_frame_nr,
                                        ainfo_ptr->extension);
    if(ainfo_ptr->new_filename == NULL)
       return -1;


    l_tmp_image_id = gap_lib_load_image(ainfo_ptr->new_filename);
    if(l_tmp_image_id < 0)
       return -1;


    l_layers_list = gimp_image_get_layers(l_tmp_image_id, &l_nlayers);
    if(l_layers_list != NULL)
    {

      if(position < l_nlayers) l_tmp_layer_id = l_layers_list[position];
      else                     l_tmp_layer_id = l_layers_list[l_nlayers -1];

      g_free (l_layers_list);


      if(l_nlayers > 1)
      {

        gimp_image_remove_layer(l_tmp_image_id, l_tmp_layer_id);


        l_rc = gap_lib_save_named_frame(l_tmp_image_id, ainfo_ptr->new_filename);
      }
    }


    gimp_image_delete(l_tmp_image_id);

    if(ainfo_ptr->run_mode == GIMP_RUN_INTERACTIVE)
    {
      l_percentage += l_percentage_step;
      gimp_progress_update (l_percentage);
    }


    if((l_cur_frame_nr == l_end) || (l_rc < 0))
       break;
    l_cur_frame_nr += l_step;

  }


  return l_rc;
}

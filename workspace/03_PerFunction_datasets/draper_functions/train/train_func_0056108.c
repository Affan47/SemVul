navi_playback(gboolean use_gimp_layeranimplayer)
{
   SelectedRange *range_list;
   gint32         l_from;
   gint32         l_to;

   gint32         l_new_image_id;
   GimpParam     *return_vals;
   int            nreturn_vals;
   char           l_frame_name[50];
   int            l_frame_delay;
   gint32         dummy_layer_id;


  if(gap_debug) printf("navi_dialog_vcr_play_callback\n");

  navi_set_waiting_cursor();

  strcpy(l_frame_name, "frame_[######]");
  if(naviD->vin_ptr)
  {
    if(naviD->vin_ptr->framerate > 0)
    {
       l_frame_delay = 1000 / naviD->vin_ptr->framerate;
       g_snprintf(l_frame_name, sizeof(l_frame_name), "frame_[######] (%dms)", (int)l_frame_delay);
    }
  }

  l_from = naviD->ainfo_ptr->first_frame_nr;
  l_to   = naviD->ainfo_ptr->last_frame_nr;

  range_list = naviD->sel_range_list;
  if(range_list)
  {
     l_to   = naviD->ainfo_ptr->first_frame_nr;
     l_from = naviD->ainfo_ptr->last_frame_nr;

     while(range_list)
     {
        l_from = MIN(l_from, range_list->from);
        l_to   = MAX(l_to,   range_list->to);
        range_list = range_list->next;
     }
  }

  if(!use_gimp_layeranimplayer)
  {


     dummy_layer_id = gap_image_get_any_layer(naviD->active_imageid);
     return_vals = gimp_run_procedure ("plug_in_gap_videoframes_player",
                                    &nreturn_vals,
                                    GIMP_PDB_INT32,    GIMP_RUN_NONINTERACTIVE,
                                    GIMP_PDB_IMAGE,    naviD->active_imageid,
                                    GIMP_PDB_DRAWABLE, dummy_layer_id,
                                    GIMP_PDB_INT32,    l_from,
                                    GIMP_PDB_INT32,    l_to,
                                    GIMP_PDB_INT32,    TRUE,
                                    GIMP_PDB_INT32,    TRUE,
                                    GIMP_PDB_INT32,    TRUE,
                                    GIMP_PDB_INT32,    TRUE,
                                    GIMP_PDB_INT32,    TRUE,
                                    GIMP_PDB_INT32,    FALSE,
                                    GIMP_PDB_FLOAT,    -1.0,
                                    GIMP_PDB_INT32,    -1,
                                    GIMP_PDB_INT32,    -1,
                                    GIMP_PDB_INT32,    FALSE,
                                    GIMP_PDB_STRING,   "\0",
                                    GIMP_PDB_INT32,    0,
                                    GIMP_PDB_FLOAT,    1.0,
                                    GIMP_PDB_END);
     gimp_destroy_params(return_vals, nreturn_vals);
     navi_set_active_cursor();
     return;
  }


  dummy_layer_id = gap_image_get_any_layer(naviD->active_imageid);
  return_vals = gimp_run_procedure ("plug_in_gap_range_to_multilayer",
                                    &nreturn_vals,
                                    GIMP_PDB_INT32,    GIMP_RUN_NONINTERACTIVE,
                                    GIMP_PDB_IMAGE,    naviD->active_imageid,
                                    GIMP_PDB_DRAWABLE, dummy_layer_id,
                                    GIMP_PDB_INT32,    l_from,
                                    GIMP_PDB_INT32,    l_to,
                                    GIMP_PDB_INT32,    3,
                                    GIMP_PDB_INT32,    1,
                                    GIMP_PDB_INT32,    (gint32)naviD->vin_ptr->framerate,
                                    GIMP_PDB_STRING,   l_frame_name,
                                    GIMP_PDB_INT32,    6,
                                    GIMP_PDB_INT32,    0,
                                    GIMP_PDB_INT32,    0,
                                    GIMP_PDB_STRING,   "0",
                                    GIMP_PDB_INT32,    0,
                                   GIMP_PDB_END);

  if (return_vals[0].data.d_status == GIMP_PDB_SUCCESS)
  {
     l_new_image_id = return_vals[1].data.d_image;
     gimp_destroy_params(return_vals, nreturn_vals);


      dummy_layer_id = gap_image_get_any_layer(l_new_image_id);
      return_vals = gimp_run_procedure ("plug_in_animationplay",
                                    &nreturn_vals,
                                    GIMP_PDB_INT32,    GIMP_RUN_NONINTERACTIVE,
                                    GIMP_PDB_IMAGE,    l_new_image_id,
                                    GIMP_PDB_DRAWABLE, dummy_layer_id,
                                   GIMP_PDB_END);
      gimp_destroy_params(return_vals, nreturn_vals);
  }
  else
  {
     gimp_destroy_params(return_vals, nreturn_vals);
  }
  navi_set_active_cursor();
}

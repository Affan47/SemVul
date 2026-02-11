p_stb_render_composite_image_postprocessing(GapStbFetchData *gfd
  , GapStoryRenderVidHandle *vidhand
  , gint32 master_frame_nr
  , gint32  vid_width, gint32  vid_height
  , char *filtermacro_file
  , const char *section_name
  )
{
  gint          l_nlayers;
  gint32       *l_layers_list;

  if(gfd->comp_image_id  < 0)
  {


    gfd->comp_image_id = p_create_unicolor_image(&gfd->layer_id
                         , vid_width
                         , vid_height
                         , 0.0
                         , 0.0
                         , 0.0
                         , 1.0
                         );
  }

  if(vidhand->is_mask_handle == TRUE)
  {


    if(gimp_image_base_type(gfd->comp_image_id) != GIMP_GRAY)
    {
      gimp_image_convert_grayscale(gfd->comp_image_id);
    }
  }


  if(1==0)
  {
    p_debug_dup_image(gfd->comp_image_id);
  }


  l_layers_list = gimp_image_get_layers(gfd->comp_image_id, &l_nlayers);
  if(l_layers_list != NULL)
  {
    gfd->layer_id = l_layers_list[0];
    g_free (l_layers_list);
  }


  if((vidhand->is_mask_handle != TRUE)
  && (section_name == NULL))
  {


    p_frame_backup_save(  GAP_VID_ENC_SAVE_MULTILAYER
                      , gfd->comp_image_id
                      , gfd->layer_id
                      , master_frame_nr
                      , TRUE
                      );
  }

  if((l_nlayers > 1 )
  || (gimp_drawable_has_alpha(gfd->layer_id)))
  {
     if(gap_debug)
     {
      printf("DEBUG: p_stb_render_composite_image_postprocessing flatten Composite image\n");
     }


     gfd->layer_id = gimp_image_flatten (gfd->comp_image_id);
  }


  p_exec_filtermacro(gfd->comp_image_id
                    , gfd->layer_id
                    , filtermacro_file
                    , NULL
                    , 0.0
                    , 1
                    );


  if ((gimp_image_width(gfd->comp_image_id) != vid_width)
  ||  (gimp_image_height(gfd->comp_image_id) != vid_height) )
  {
     if(gap_debug) printf("DEBUG: p_story_render_fetch_composite_image_private: scaling tmp image\n");

     gimp_image_scale(gfd->comp_image_id, vid_width, vid_height);
  }


  l_layers_list = gimp_image_get_layers(gfd->comp_image_id, &l_nlayers);
  if(l_layers_list != NULL)
  {
    gfd->layer_id = l_layers_list[0];
    g_free (l_layers_list);
  }
  if((l_nlayers > 1 )
  || (gimp_drawable_has_alpha(gfd->layer_id)))
  {
     if(gap_debug) printf("DEBUG: p_story_render_fetch_composite_image_private  FINAL flatten Composite image\n");


      gfd->layer_id = gimp_image_flatten (gfd->comp_image_id);
  }

}

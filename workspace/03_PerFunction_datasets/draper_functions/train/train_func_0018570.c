p_fetch_composite_image(GapPlayerMainGlobalParams *gpp
                   , gint32 framenumber
                   , gint32 width
                   , gint32 height
                   )
{
  gint32 composite_image_id;

  composite_image_id = -1;
  if(gpp->stb_ptr == NULL)
  {
    return (composite_image_id);
  }

#ifdef GAP_ENABLE_VIDEOAPI_SUPPORT


  if ((gpp->stb_comp_vidhand == NULL)
  ||  (gpp->stb_parttype != gpp->stb_ptr->stb_parttype)
  ||  (gpp->stb_unique_id != gpp->stb_ptr->stb_unique_id))
  {
    p_open_composite_storyboard(gpp);
  }

  if(gpp->stb_comp_vidhand)
  {
      gint32 l_layer_id;
      l_layer_id = -1;


      composite_image_id = gap_story_render_fetch_composite_image(
                               gpp->stb_comp_vidhand
                               , framenumber
                               , width
                               , height
                               , NULL
                               , &l_layer_id
                               );
       if(gap_debug)
       {
         printf("p_fetch_composite_image: comp_vidhand:%d  composite_image_id:%d\n"
             ,(int)gpp->stb_comp_vidhand
             ,(int)composite_image_id
             );
       }
  }

#endif
  return (composite_image_id);
}

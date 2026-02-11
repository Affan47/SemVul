gap_story_render_open_vid_handle(GapLibTypeInputRange input_mode
                      , gint32 image_id
                      , const char *storyboard_file
                      , const char *basename
                      , const char *ext
                      , gint32  frame_from
                      , gint32  frame_to
                      , gint32 *frame_count
                      )
{
  GapStoryRenderVidHandle *l_vidhand;
  char *imagename;

  imagename = NULL;
  if(image_id >= 0)
  {
    imagename = gimp_image_get_filename(image_id);
  }
  l_vidhand = p_open_video_handle_private( TRUE
                            , FALSE
                            , FALSE
                            , NULL
                            , NULL
                            , 0
                            ,storyboard_file
                            ,basename
                            ,ext
                            ,frame_from
                            ,frame_to
                            ,frame_count
                            ,TRUE
                            ,input_mode
                            ,imagename
                            ,NULL
                            ,1
                            ,0
                            ,0.0
                            ,TRUE
                            ,NULL
                            );

  if(imagename)
  {
    g_free(imagename);
  }
  return(l_vidhand);
}

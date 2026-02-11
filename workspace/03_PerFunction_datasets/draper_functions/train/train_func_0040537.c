gap_story_adjust_size_respecting_aspect(GapStoryBoard *stb
                         ,gint32 *width
                         ,gint32 *height)
{
  gdouble aspect_ratio;

  aspect_ratio  = 0.0;
  if(stb->master_aspect_height > 0)
  {
    stb->master_aspect_ratio = (gdouble)stb->master_aspect_width
                             / (gdouble)stb->master_aspect_height;
  }


  if(stb->master_aspect_ratio > 0.0)
  {
    gdouble asp_height;

    asp_height = (gdouble)(*width) / stb->master_aspect_ratio;
    *height = (gint32)asp_height;
    aspect_ratio = stb->master_aspect_ratio;
  }

  if(gap_debug)
  {
    printf("gap_story_adjust_size_respecting_aspect aspect:%f master_asp (%d x %d) result: (%d x %d)\n"
      ,(float)stb->master_aspect_ratio
      ,(int)stb->master_aspect_width
      ,(int)stb->master_aspect_height
      ,(int)*width
      ,(int)*height
      );
  }

  return(aspect_ratio);


}

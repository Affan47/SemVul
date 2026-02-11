gap_story_count_total_frames_in_section(GapStorySection  *section)
{
  GapStoryElem      *stb_elem;
  gint32             l_total_frames;
  gint32             l_framecount[GAP_STB_MAX_VID_TRACKS];
  gint32             l_overlap_request[GAP_STB_MAX_VID_TRACKS];
  gint ii;

  if (section == NULL)
  {
    printf("** ERROR gap_story_count_total_frames_in_section section is NULL\n");
    return(0);
  }

  for(ii=0; ii < GAP_STB_MAX_VID_TRACKS; ii++)
  {
    l_overlap_request[ii] = 0;
    l_framecount[ii] = 0;
  }

  for(stb_elem = section->stb_elem; stb_elem != NULL;  stb_elem = stb_elem->next)
  {
    gint32             l_overlap_new;
    gint32             l_overlap_actual;

    if(gap_story_elem_is_video_relevant(stb_elem) != TRUE)
    {
      continue;
    }

    l_overlap_new = p_story_elem_calculate_nframes(stb_elem);
    l_overlap_request[stb_elem->track] += l_overlap_new;
    l_framecount[stb_elem->track] = l_framecount[stb_elem->track] + stb_elem->nframes;
    l_overlap_actual = MIN(MAX(0, l_framecount[stb_elem->track]), l_overlap_request[stb_elem->track]);

    l_framecount[stb_elem->track] -= l_overlap_actual;
    l_overlap_request[stb_elem->track] -= l_overlap_actual;
  }

  l_total_frames = 0;
  for(ii=0; ii < GAP_STB_MAX_VID_TRACKS; ii++)
  {
    l_total_frames = MAX(l_framecount[ii], l_total_frames);
  }

  return(l_total_frames);

}

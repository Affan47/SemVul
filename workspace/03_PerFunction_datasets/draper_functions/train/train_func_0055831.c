gap_story_get_expanded_framenr_by_story_id(GapStorySection *section, gint32 story_id, gint32 in_track)
{
  GapStoryElem      *stb_elem;
  gint32             l_framenr;
  gint32             l_framecount;

  l_framecount = 0;

  for(stb_elem = section->stb_elem; stb_elem != NULL;  stb_elem = stb_elem->next)
  {
    if(stb_elem->track != in_track)
    {
      continue;
    }
    if(gap_story_elem_is_video_relevant(stb_elem) != TRUE)
    {
      continue;
    }
    if(stb_elem->story_id == story_id)
    {
      break;
    }
    p_story_elem_calculate_nframes(stb_elem);
    l_framecount = l_framecount + stb_elem->nframes;
  }
  l_framenr = l_framecount + 1;
  return(l_framenr);

}

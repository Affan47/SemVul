gap_story_fetch_nth_active_elem(GapStoryBoard *stb
                              , gint32 seq_nr
                              , gint32 in_track
                              )
{
  gint32             cnt_active_elements;
  GapStoryElem *stb_elem;

  cnt_active_elements = 0;
  if (stb->active_section == NULL)
  {
    return (NULL);
  }

  for(stb_elem = stb->active_section->stb_elem; stb_elem != NULL;  stb_elem = stb_elem->next)
  {
    if(stb_elem->track == in_track)
    {
      if(gap_story_is_active_element(stb_elem))
      {
        cnt_active_elements++;
        if(cnt_active_elements == seq_nr)
        {
          return(stb_elem);
        }
      }
    }
  }

  return(NULL);
}

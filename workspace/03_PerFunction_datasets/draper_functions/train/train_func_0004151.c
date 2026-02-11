gap_story_enable_hidden_maskdefinitions(GapStoryBoard *stb_ptr)
{
  GapStoryElem  *stb_elem;

  if (stb_ptr->mask_section == NULL)
  {
    return;
  }

  for(stb_elem = stb_ptr->mask_section->stb_elem; stb_elem != NULL;  stb_elem = stb_elem->next)
  {
    if(stb_elem->track == GAP_STB_HIDDEN_MASK_TRACK_NUMBER)
    {
      stb_elem->track = GAP_STB_MASK_TRACK_NUMBER;
    }
  }
}

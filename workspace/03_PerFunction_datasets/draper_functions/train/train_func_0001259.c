gap_story_selection_all_set(GapStoryBoard *stb, gboolean sel_state)
{
  GapStoryElem *stb_elem;
  GapStorySection *section;

  if(stb  == NULL)   { return; }
  for(section = stb->stb_section; section != NULL; section = section->next)
  {
    for(stb_elem = section->stb_elem; stb_elem != NULL;  stb_elem = stb_elem->next)
    {
      stb_elem->selected = sel_state;
    }
  }


}

gap_story_elem_find_in_section_by_story_id(GapStorySection *section, gint32 story_id)
{
  GapStoryElem *stb_elem;

  if(section)
  {
      for(stb_elem = section->stb_elem; stb_elem != NULL;  stb_elem = stb_elem->next)
      {
        if(stb_elem->story_id == story_id)
        {
          return(stb_elem);
        }
      }
  }
  return (NULL);

}

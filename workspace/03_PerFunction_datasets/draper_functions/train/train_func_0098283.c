gap_story_free_storyboard(GapStoryBoard **stb_ptr)
{
  GapStoryBoard *stb;

  stb = *stb_ptr;
  if(stb)
  {
    if(stb->stb_section)
    {
      GapStorySection *stb_section;
      stb_section = stb->stb_section;
      while(stb_section != NULL)
      {
        GapStorySection *stb_section_next;

        stb_section_next = stb_section->next;
        gap_story_free_stb_section(stb_section);
        stb_section = stb_section_next;
      }
      stb->stb_section = NULL;
    }


    if(stb->edit_settings)
    {
       if (stb->edit_settings->section_name)
       {
         g_free(stb->edit_settings->section_name);
       }
       g_free(stb->edit_settings);
       stb->edit_settings = NULL;
    }


    if(stb->mapping)
    {
      gap_story_free_selection_mapping(stb->mapping);
      stb->mapping = NULL;
    }


    stb->active_section = NULL;
    stb->mask_section = NULL;

    if(stb->storyboardfile)
    {
      g_free(stb->storyboardfile);
    }
    if(stb->errtext)
    {
      g_free(stb->errtext);
    }
    if(stb->errline)
    {
      g_free(stb->errline);
    }
    if(stb->warntext)
    {
      g_free(stb->warntext);
    }
    if(stb->warnline)
    {
      g_free(stb->warnline);
    }
    if(stb->master_insert_area_format)
    {
      g_free(stb->master_insert_area_format);
    }


  }
  *stb_ptr = NULL;
}

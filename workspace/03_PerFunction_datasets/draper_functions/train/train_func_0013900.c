p_build_frame_cache(t_GVA_Handle *gvahand, gint32 frames_to_keep_cahed)
{
  t_GVA_Frame_Cache *fcache;
  t_GVA_Frame_Cache_Elem  *fc_ptr;

  fcache = &gvahand->fcache;
  fcache->frame_cache_size = 0;
  if(fcache->fc_current)
  {
    fcache->frame_cache_size = 1;
    fc_ptr = (t_GVA_Frame_Cache_Elem  *)fcache->fc_current->next;
    while(fcache->fc_current != fc_ptr)
    {
      fcache->frame_cache_size++;
      fc_ptr = (t_GVA_Frame_Cache_Elem  *)fc_ptr->next;
      if(fc_ptr == NULL)
      {
         printf("API internal ERROR (frame cache is not linked as ring)\n");
         exit(1);
      }
    }


    while(fcache->frame_cache_size > frames_to_keep_cahed)
    {
      p_drop_next_frame_cache_elem(fcache);
      fcache->frame_cache_size--;
    }
  }
  else
  {

    fc_ptr = p_new_frame_cache_elem(gvahand);
    fc_ptr->prev = fc_ptr;
    fc_ptr->next = fc_ptr;
    fcache->fc_current = fc_ptr;
    gvahand->frame_data = fc_ptr->frame_data;
    gvahand->row_pointers = fc_ptr->row_pointers;
    fcache->frame_cache_size = 1;
  }


  while(fcache->frame_cache_size < frames_to_keep_cahed)
  {
    t_GVA_Frame_Cache_Elem  *fc_nxt;


    fc_nxt = (t_GVA_Frame_Cache_Elem  *)fcache->fc_current->next;

    fc_ptr = p_new_frame_cache_elem(gvahand);
    fc_ptr->prev = fcache->fc_current;
    fc_ptr->next = fc_nxt;
    fc_nxt->prev = fc_ptr;
    fcache->fc_current->next = fc_ptr;

    fcache->frame_cache_size++;
  }

  return(fcache->frame_cache_size);

}

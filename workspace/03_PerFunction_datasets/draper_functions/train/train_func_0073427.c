p_debug_print_vthumbs_refering_video_id(GapVThumbElem *vthumb_list, gint32 video_id)
{
  GapVThumbElem *vthumb_elem;

  printf("        vthumbs: [");
  for(vthumb_elem = vthumb_list; vthumb_elem != NULL; vthumb_elem = vthumb_elem->next)
  {
    if(vthumb_elem->video_id == video_id)
    {
      printf(" %06d", (int)vthumb_elem->framenr);
    }
  }
  printf("]\n");

}

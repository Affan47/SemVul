p_check_image_numpart (GapStoryElem *stb_elem, char *filename)
{
  char *l_basnam;
  long  l_number;

  l_basnam = gap_lib_alloc_basename(filename, &l_number);
  if(l_basnam)
  {
    if(l_number > 0)
    {

      stb_elem->from_frame = l_number;
      stb_elem->to_frame   = l_number;
    }
    g_free(l_basnam);
  }
}

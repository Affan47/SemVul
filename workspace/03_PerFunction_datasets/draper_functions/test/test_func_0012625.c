p_assign_parsed_flip_value(GapStoryElem *stb_elem
  , char *flip_ptr
  )
{
  if(flip_ptr)
  {
    if(*flip_ptr)
    {
      switch(*flip_ptr)
      {
        case 'n':
        case 'N':
          stb_elem->flip_request = GAP_STB_FLIP_NONE;
          break;
        case 'h':
        case 'H':
          stb_elem->flip_request = GAP_STB_FLIP_HOR;
          break;
        case 'v':
        case 'V':
          stb_elem->flip_request = GAP_STB_FLIP_VER;
          break;
        case 'b':
        case 'B':
          stb_elem->flip_request = GAP_STB_FLIP_BOTH;
          break;
      }
    }
  }

}
